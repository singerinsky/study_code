#ifndef C3D21E3C_80A5_4FE8_B8CC_4642BCE537E3
#define C3D21E3C_80A5_4FE8_B8CC_4642BCE537E3

#include <iostream>
template <class N>
class tree_iterator{
    const N *pos_;
public:
    typedef typename N::value_type value_type;
    typedef typename N::const_reference_type const_refernce_type;
    typedef tree_iterator<N> self_type;
    tree_iterator():pos_(nullptr){}
    tree_iterator(const N*pos):pos_(pos){}
    bool operator==(self_type const& right)const{
        return pos_ == right.pos_;
    }

    self_type& operator++(){
        if(pos_)
        {
            if(pos_->right_)
            {
                pos_ = pos_->right_;
                while(pos_->left_)
                    pos_ = pos_->left_;
            }else{
                while ((pos_->parent_)&&
                (pos_->parent_->right_ == pos_))
                {
                    /* code */
                    pos_ = pos_->parent_;
                }
                pos_ = pos_->parent_;
            }
        }
        return *this;
    }

    const_refernce_type operator*()const 
    {
            return pos_->value_;
    }
};

template<class N>
bool operator != (tree_iterator<N> const &left,tree_iterator<N>const &right)
{
    return !(left == right);
}

template <typename... Mixins> class Point : public Mixins... {
  public:
    double x, y;
    Point() : Mixins()..., x(0.0), y(0.0) {}
    Point(double x, double y) : Mixins()..., x(x), y(y) {}
    void Display() const { std::cout << "(" << x << ", " << y << ")"; }
};

class Label {
  public:
    std::string label;
    Label() : label("Y") {}
};

class Color {
  public:
    unsigned char red = 1, green = 1, blue = 1;
};

using MixClass = Point<Label, Color>;

#endif /* C3D21E3C_80A5_4FE8_B8CC_4642BCE537E3 */
