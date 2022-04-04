#ifndef E9B397CC_6E72_4679_978A_1F8B1CF4E195
#define E9B397CC_6E72_4679_978A_1F8B1CF4E195
#include "../header.h"
#include <new>

/*
template <typename T> struct AllocatorWrapper {
  mutable Arena *arena_;
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  AllocatorWrapper(const AllocatorWrapper &p) : arena_(p.arena_) {}
  AllocatorWrapper(Arena *q) : arena_(q) {}
  T *allocate(size_t size) {
    auto q = reinterpret_cast<T *>(arena_->Allocate(size * sizeof(T)));
    return q;
  }
  void deallocate(void *p, size_type n) {}
  template <class U> struct rebind { typedef AllocatorWrapper<U> other; };
  void construct(pointer p, const T &value) { new (p) T(value); }
  template <class... Args> void construct(pointer p, Args &&...args) {
    new (p) T(std::forward<Args>(args)...);
  }
  void destroy(pointer p) { p->~T(); }
  pointer address(reference x) { return (pointer)&x; }
  const_pointer address(const_reference x) { return (const_pointer)&x; }
  size_type max_size() const { return size_type(UINT_MAX / sizeof(T)); }
};
*/
#endif /* E9B397CC_6E72_4679_978A_1F8B1CF4E195 */
