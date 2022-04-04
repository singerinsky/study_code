#ifndef A5CCB58B_F3C0_414A_95F6_DDA56C80DBBE
#define A5CCB58B_F3C0_414A_95F6_DDA56C80DBBE

struct Point {
  float x;
  float y;
};

class CRectangle {
public:
  CRectangle() {}
  CRectangle(Point pos, float w, float h) {
    m_pos = pos;
    m_width = w;
    m_height = h;
  }

  bool Contains(CRectangle &rect) const { return true; }

  bool HasArea() const {
    if (m_height * m_width < 0.001f)
      return false;
    return true;
  }

  bool IntersectsWith(CRectangle &rect) const { return false; }

  Point m_pos;
  float m_width;
  float m_height;
};

#endif /* A5CCB58B_F3C0_414A_95F6_DDA56C80DBBE */
