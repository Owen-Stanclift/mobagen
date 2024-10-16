#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);

  std::vector<Point2D> getVisitables(World* w, const Point2D& p);

  Point2D probableExit(const Point2D& p,World* w);
  Point2D searchNearestExit(const Point2D&,World* w);
  int cost(Point2D p1, Point2D p2);

  Point2D exit;


private:
  std::unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  std::unordered_map<Point2D, bool> visited;
  Point2D leastPoint;
  struct Node {
    Point2D p;
    int cost;
    int hCost;

    bool operator<(const Node &other) const{
      return cost + hCost > other.cost + other.hCost;
    }
  };
};


#endif  // AGENT_H
