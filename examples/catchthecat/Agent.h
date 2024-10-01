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



private:
  std::unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  std::queue<Point2D> frontier;                   // to store next ones to visit
  std::unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  std::unordered_map<Point2D, bool> visited;
};


#endif  // AGENT_H
