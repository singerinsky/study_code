#ifndef DA4124AB_65EB_4B93_8C11_64154D75C8E8
#define DA4124AB_65EB_4B93_8C11_64154D75C8E8

#include "rectangle.h"
#include <vector>

class ObjectRect {
public:
  CRectangle &GetRect() { return m_rect; }
  CRectangle m_rect;
};

class CQuadTreeNode {
public:
  CQuadTreeNode() {}
  CQuadTreeNode(CRectangle &rect) { m_bounds = rect; }
  int GetCount() {
    int count = 0;
    for (auto &itr : m_nodes) {
      count += itr.GetCount();
    }
    return count + m_contents.size();
  }
  CQuadTreeNode(CRectangle &&rect) { m_bounds = rect; }

  std::vector<ObjectRect> GetSubTreeContents() {
    std::vector<ObjectRect> vec;
    for (auto &itr : m_nodes) {
      auto sub_contents = itr.GetSubTreeContents();
      vec.insert(vec.end(), sub_contents.begin(), sub_contents.end());
    }
    vec.insert(vec.end(), m_contents.begin(), m_contents.end());
    return vec;
  }

  std::vector<ObjectRect> GetContents() { return m_contents; }

  void Insert(ObjectRect t) {
    if (!m_bounds.Contains(t.GetRect())) {
      return;
    }

    if (m_nodes.size() == 0) {
      CreateSubNodes();
    }

    for (auto &itr : m_nodes) {
      if (itr.m_bounds.Contains(t.GetRect())) {
        itr.Insert(t);
        return;
      }
    }

    m_contents.emplace_back(t);
  }

  void CreateSubNodes() {
    if (!m_bounds.HasArea())
      return;
    float halfWidth = (m_bounds.m_width / 2.f);
    float halfHeight = (m_bounds.m_height / 2.f);
    Point location_one = m_bounds.m_pos;
    m_nodes.emplace_back(std::move(CQuadTreeNode(
        std::move(CRectangle(location_one, halfWidth, halfHeight)))));
    Point location_two = m_bounds.m_pos;
    location_two.x += halfWidth;
    m_nodes.emplace_back(std::move(CQuadTreeNode(
        std::move(CRectangle(location_two, halfWidth, halfHeight)))));
    Point location_three = m_bounds.m_pos;
    location_three.y += halfHeight;
    location_three.x += halfWidth;
    m_nodes.emplace_back(std::move(CQuadTreeNode(
        std::move(CRectangle(location_three, halfWidth, halfHeight)))));
    Point location_four = m_bounds.m_pos;
    location_four.y += halfHeight;
    m_nodes.emplace_back(std::move(CQuadTreeNode(
        std::move(CRectangle(location_four, halfWidth, halfHeight)))));
  }

  bool IsEmpty() { return m_contents.empty() && m_nodes.empty(); }

  std::vector<ObjectRect> Query(CRectangle &rect) {
    std::vector<ObjectRect> vec;
    for (auto &itr : m_contents) {
      if (rect.IntersectsWith(itr.GetRect())) {
        vec.emplace_back(itr);
      }
    }

    for (auto &node : m_nodes) {
      if (node.IsEmpty())
        continue;

      if (node.GetBound().Contains(rect)) {
        auto sub_vec = node.Query(rect);
        vec.insert(vec.end(), sub_vec.begin(), sub_vec.end());
        break;
      }

      if (node.GetBound().IntersectsWith(rect)) {
        auto sub_vec = node.Query(rect);
        vec.insert(vec.end(), sub_vec.begin(), sub_vec.end());
      }
    }

    return vec;
  }

  const CRectangle &GetBound() { return m_bounds; }

protected:
  CRectangle m_bounds;
  std::vector<ObjectRect> m_contents;
  std::vector<CQuadTreeNode> m_nodes;
};

class CQuadTree {
protected:
  CQuadTreeNode m_root;
  CRectangle m_root_rect;

public:
  CQuadTree(const CRectangle &rect) { m_root_rect = rect; }

  int Count() { return m_root.GetCount(); }

  void Insert(ObjectRect item) { m_root.Insert(item); }

  std::vector<ObjectRect> Query(CRectangle &area) { return m_root.Query(area); }
};
#endif /* DA4124AB_65EB_4B93_8C11_64154D75C8E8 */
