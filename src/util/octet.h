#ifndef F0403199_EC48_41F8_8165_D851004D1AE6
#define F0403199_EC48_41F8_8165_D851004D1AE6
//#define _REENTRANT_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

inline void* fast_memmove(void* dest, const void* src, size_t n)
{
	char* d = static_cast<char*>(dest);
	const char* s = static_cast<const char*>(src);

	if ( s < d && s + n >= d )
		return memmove(dest, src, n);
	else
		return memcpy(dest, src, n);
}

class Octets
{
	struct Rep
	{
		size_t cap;
		size_t len;
		size_t ref;

		//是否可重入,多线程
#if defined _REENTRANT_
#ifdef WIN32
		void addref()  { InterlockedIncrement((LONG*)&ref); }
		void release() { if (0 == InterlockedDecrement((LONG*)&ref)) delete this; }
#else
		void addref()
		{
			__asm__ __volatile__ (
					"lock; add $1, %0	\n"
					: "=m"(ref)
					);
		}

		void release()
		{
			size_t old;
			__asm__ __volatile__ (
					"lock; xadd  %2, %0	\n"
					: "=m"(ref), "=r"(old)
					: "1"(-1) : "memory"
					);

			if ( old == 1 ) delete this;
		}
#endif
#else
		void addref() { ref++; }
		void release() { if (--ref == 0) delete this; }
#endif
		//因为重载了new ，所以他的数据区的，起始位置就是在其指针地址+class size
		void* data() { return reinterpret_cast<void*>(this + 1); }

		void* clone()
		{
			Rep* rep = create(cap);
			memcpy(rep->data(), data(), rep->len = len);
			return rep->data();
		}

		void* unique()
		{
			if (ref > 1)
			{
				void* r = clone();
				release();
				return r;
			}
			return data();
		}

		void* reserve(size_t size)
		{
			size = frob_size(size);
			if ( size > cap )
			{
				Rep* rep = create(size);
				memcpy(rep->data(), data(), rep->len = len);
				release();
				return rep->data();
			}
			return unique();
		}

		static size_t frob_size(size_t size)
		{
			size_t tmp = 16;
			while ( size > tmp ) tmp <<= 1;
			return tmp;
		}

		static Rep* create(size_t cap)
		{
			Rep* rep = new (cap) Rep;
			rep->cap = cap;
			rep->len = 0;
			rep->ref = 1;
			return rep;
		}

		static void* operator new (size_t size, size_t extra) { return malloc(size + extra); }
		static void  operator delete (void* p) { free(p); }
		static Rep& null_rep(void)
		{
			static Rep null = { 0, 0, 1 };
			return null;
		}
	};

	void* base;
	Rep* rep () const { return reinterpret_cast<Rep*>(base) - 1; }
	void unique() { base = rep()->unique(); }

	public:
	Octets() : base(Rep::null_rep().data()) { rep()->addref(); }
	Octets(size_t size) : base(Rep::create(size)->data()) { }

	Octets(const void* beg, size_t size) : base(Rep::create(size)->data())
	{
		memcpy(base, beg, size);
		rep()->len = size;
	}

	Octets(const void* beg, const void* end)
	{
		size_t size = static_cast<const char*>(end) - static_cast<const char*>(beg);
		base = Rep::create(size)->data();

		memcpy(base, beg, size);
		rep()->len = size;
	} 

	Octets(const Octets& o) : base(o.base) { rep()->addref(); }
	virtual ~Octets() { rep()->release(); }

	Octets& operator= (const Octets& o)
	{
		if (this != &o)
		{
			rep()->release();
			base = o.base;
			rep()->addref();
		}
		return *this;
	}

	bool operator == (const Octets& o) const 
	{ 
		return size() == o.size() && !memcmp( base, o.base, size() ); 
	}

	bool operator != (const Octets& o) const { return ! operator == (o); }

	void reserve(size_t size)
	{
		base = rep()->reserve(size);
	}

	void assign(const void* beg, size_t size)
	{
		reserve(size);
		memcpy(base, beg, size);
		rep()->len = size;
	}

	void swap(Octets& o) 
	{ 
		void* tmp = base; 
		base = o.base; 
		o.base = tmp; 
	}

	void* begin() { unique(); return base; }
	void* end()   { unique(); return static_cast<char*>(base) + rep()->len; }

	const void* begin() const { return base; }
	const void* end()   const { return static_cast<const char*>(base) + rep()->len; }

	size_t size()     const { return rep()->len; }
	size_t capacity() const { return rep()->cap; }

	void clear() 
	{ 
		unique(); 
		rep()->len = 0; 
	}

	void* erase(size_t pos, size_t len) 
	{ 
		char* p = static_cast<char*>(begin()); 
		return erase(p + pos, p + pos + len); 
	}

	void* erase(void* beg, void* end)
	{
		if (beg != end)
		{
			void* tmp = base;
			base = rep()->unique();
			ptrdiff_t diff = static_cast<char*>(base) - static_cast<char*>(tmp);

			if (0 != diff)
			{
				beg = static_cast<char*>(beg) + diff;
				end = static_cast<char*>(end) + diff;
			}

			fast_memmove(beg, end, (static_cast<char*>(base) + rep()->len) - static_cast<char*>(end));
			rep()->len -= static_cast<char*>(end) - static_cast<char*>(beg);
		}
		return beg;
	}

	void insert(void* pos, const void* beg, size_t len)
	{
		ptrdiff_t offset = static_cast<char*>(pos) - static_cast<char*>(base);
		reserve(size() + len);
		pos = static_cast<char*>(base) + offset;

		size_t adjust = size() - offset;
		if (adjust) 
			fast_memmove(static_cast<char*>(pos) + len, pos, adjust);

		fast_memmove(pos, beg, len);
		rep()->len += len;
	}

	void insert(void* pos, const void* beg, const void* end) 
	{ 
		insert(pos, beg, static_cast<const char*>(end) - static_cast<const char*>(beg)); 
	}

	void resize(size_t size) 
	{ 
		reserve(size); 
		rep()->len = size; 
	}

	void dump()
	{
		const unsigned char* p = (const unsigned char*)begin();
		for(size_t i = 0; i < size(); i++)
			fprintf(stderr, "%02x ", *p++);
		fprintf(stderr, "\n");
	}
};


#endif /* F0403199_EC48_41F8_8165_D851004D1AE6 */
