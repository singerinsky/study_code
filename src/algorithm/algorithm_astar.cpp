#include "../header.h"
#include <cmath>
#include <cstring>
#include <queue>

//水平 或者 垂直移动cost
constexpr int NormalCost = 10;
//斜方向移动cost
constexpr int DiagonalCost = 14;

struct PointCell {
  int index;
  int x, y;
  int parent_index;
  int isblock;
  int F, G, H; // F=G+H

  // G:从起点到当前点消耗  H:该点到终点的预估消耗
  PointCell() { memset(this, 0, sizeof(PointCell)); }
  PointCell(int index, int isblock) : index(index), isblock(isblock) {
    parent_index = 0;
  }

  int CalcMoveCost(const PointCell *pCell) {
    return (abs((pCell->x - x) + abs(pCell->y - y)) == 1) ? NormalCost
                                                          : DiagonalCost;
  }
  // 重载小于号，便于优先队列排序
  bool operator<(const PointCell &cell) const { return F < cell.F; }

  bool operator<(const PointCell *cell) const { return F < cell->F; }

  void Dump() const {
    LOG(INFO) << "Point:" << index << " x:" << x << " y:" << y
              << " parent_index:" << parent_index << " isblock:" << isblock
              << " F:" << F << " G:" << G << " H:" << H;
  }
};

class MapAStar {
public:
  MapAStar() {}

  virtual ~MapAStar() {}
  void Init() { cells_index_.resize(width * height); }

  void InitCell(int index, int isblock) {
    int xindex = index / width;
    int yindex = index % height;
    cells_index_[index].index = index;
    cells_index_[index].x = xindex;
    cells_index_[index].y = yindex;
    cells_index_[index].isblock = isblock;
  }

  PointCell *GetCell(int index) { return &cells_index_[index]; }

  PointCell *GetCell(int x, int y) {
    int index = x * width + y;
    return &cells_index_[index];
  }

  int GetSize() { return cells_index_.size(); }

  std::vector<int> GetNeighbors(int x, int y) {
    std::vector<int> vec;
    for (int xstart = x - 1; xstart <= x + 1; xstart++) {
      for (int ystart = y - 1; ystart <= y + 1; ystart++) {
        if (xstart < 0 || xstart >= width || ystart < 0 || ystart >= height)
          continue;
        if (xstart == x && ystart == y)
          continue;
        int index = xstart * width + ystart;
        vec.push_back(index);
      }
    }
    return vec;
  }
  int ConvertXYToIndex(int x, int y) { return x * width + y; }

  int CalcHValue(int index, int end_index) {
    int rst = ::sqrt((cells_index_[index].x - cells_index_[end_index].x) *
                         (cells_index_[index].x - cells_index_[end_index].x) +
                     (cells_index_[index].y - cells_index_[end_index].y) *
                         (cells_index_[index].y - cells_index_[end_index].y)) *
              NormalCost;
    return rst;
  }

  bool FindPath(int startx, int starty, int endx, int endy) {
    // const PointCell *pStartPoint = GetCell(startx, starty);
    const PointCell *pEndPoint = GetCell(endx, endy);
    std::set<int> visited;
    std::priority_queue<const PointCell *> open_list;
    open_list.push(GetCell(startx, starty));
    while (!open_list.empty()) {
      const auto *curPoint = open_list.top();
      open_list.pop();
      visited.insert(curPoint->index);

      auto neighbors = GetNeighbors(curPoint->x, curPoint->y);
      for (auto index : neighbors) {
        //跳过block
        if (cells_index_[index].isblock == 1) {
          continue;
        }

        //如果已经在openlist中的话
        if (visited.find(index) != visited.end()) {
          int tempG = curPoint->G + cells_index_[index].CalcMoveCost(curPoint);
          if (tempG < cells_index_[index].G) {
            cells_index_[index].G = tempG;
            cells_index_[index].F =
                cells_index_[index].G + cells_index_[index].H;
            cells_index_[index].parent_index = curPoint->index;
          }
        } else {
          cells_index_[index].parent_index = curPoint->index;
          cells_index_[index].G =
              curPoint->G + cells_index_[index].CalcMoveCost(curPoint);
          cells_index_[index].H = CalcHValue(index, pEndPoint->index);
          cells_index_[index].F = cells_index_[index].G + cells_index_[index].H;
          open_list.push(&cells_index_[index]);
        }

        if (cells_index_[index].x == endx && cells_index_[index].y == endy) {
          LOG(INFO) << "find path!!";
          return true;
        }
      }
    }
    LOG(INFO) << "not find path";
    return false;
  }

private:
  const int width = 6;
  const int height = 6;
  std::vector<PointCell> cells_index_;
};

void BuildRandomMapAStar(MapAStar &MapAStar) {

  MapAStar.InitCell(0, 1);
  MapAStar.InitCell(1, 1);
  MapAStar.InitCell(2, 1);
  MapAStar.InitCell(3, 1);
  MapAStar.InitCell(4, 1);
  MapAStar.InitCell(5, 1);
  MapAStar.InitCell(6, 1);
  MapAStar.InitCell(7, 0);
  MapAStar.InitCell(8, 0);
  MapAStar.InitCell(9, 0);
  MapAStar.InitCell(10, 0);
  MapAStar.InitCell(11, 1);
  MapAStar.InitCell(12, 1);
  MapAStar.InitCell(13, 1);
  MapAStar.InitCell(14, 1);
  MapAStar.InitCell(15, 1);
  MapAStar.InitCell(16, 0);
  MapAStar.InitCell(17, 1);
  MapAStar.InitCell(18, 1);
  MapAStar.InitCell(19, 1);
  MapAStar.InitCell(20, 1);
  MapAStar.InitCell(21, 1);
  MapAStar.InitCell(22, 0);
  MapAStar.InitCell(23, 1);
  MapAStar.InitCell(24, 1);
  MapAStar.InitCell(25, 1);
  MapAStar.InitCell(26, 1);
  MapAStar.InitCell(27, 0);
  MapAStar.InitCell(28, 0);
  MapAStar.InitCell(29, 1);
  MapAStar.InitCell(30, 1);
  MapAStar.InitCell(31, 1);
  MapAStar.InitCell(32, 1);
  MapAStar.InitCell(33, 1);
  MapAStar.InitCell(34, 1);
  MapAStar.InitCell(35, 1);
}

class AStarTest : public testing::Test {
protected:
  void SetUp() override {
    map = new MapAStar();
    map->Init();
    BuildRandomMapAStar(*map);
  }

  void TearDown() override { delete map; }

  MapAStar *map;
};

// 测试 MakeRecently() 方法
TEST_F(AStarTest, get_neigbor) {
  vector<int> n = map->GetNeighbors(1, 1);
  for (auto t : n) {
    LOG(INFO) << t;
  }
  LOG(INFO) << "finish test";
}

// 测试 MakeRecently() 方法
TEST_F(AStarTest, FindPath) {
  const PointCell *p = map->GetCell(4, 4);
  const PointCell *p1 = map->GetCell(1, 1);
  p->Dump();
  p1->Dump();
  std::vector<int> vecPathFind;
  bool rst = map->FindPath(1, 1, 4, 4);
  if (rst) {
    while (p->parent_index != 0) {
      p->Dump();
      vecPathFind.push_back(p->index);
      p = map->GetCell(p->parent_index);
    }
  }
  LOG(INFO) << "finish test";
}
