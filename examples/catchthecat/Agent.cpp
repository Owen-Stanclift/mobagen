#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

#include <algorithm>
#include <map>

using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  // use .at() to get data, if the element dont exist [] will give you wrong results
  std::priority_queue<Node> frontier;                   // to store next ones to visit
  std::unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  auto size = w->getWorldSideSize()/2;
  std::vector<Point2D> neighbors;
  // bootstrap state
  auto catPos = w->getCat();
  int currCost = 0;
  int heuristic = size;
  int leastCost = heuristic;
  frontier.push({catPos,currCost,heuristic});
  frontierSet.insert(catPos);
  exit = probableExit(catPos,w);
  if(w->getContent(exit)) {
    if(abs(exit.x) == size) {
      while(w->getContent(exit)) {
        if(exit.y < size)
          exit = {exit.x,exit.y+1};
        if(exit.y > -size)
          exit = {exit.x,exit.y-1};
      }
    }
    if(abs(exit.y) == size) {
      while(w->getContent(exit)) {
        if(exit.x < size)
          exit = {exit.x,exit.y+1};
        if(exit.x > -size)
          exit = {exit.x,exit.y-1};
      }
    }
  }
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
  if(catPos.x == 0 && catPos.y == 0) {
    frontier.pop();
    neighbors = getVisitables(w,catPos);
    int randNum = 0;
    std::mt19937 rng = std::mt19937(std::random_device()());
    std::uniform_int_distribution<int> range(0,neighbors.size());
    randNum = range(rng);
    Point2D nextPos = neighbors[randNum];
    heuristic = size-1;
    leastCost = heuristic;
    frontier.push({nextPos,currCost+1,heuristic});
    cameFrom[nextPos] = catPos;
    exit = probableExit(nextPos,w);
  }


  while (!frontier.empty()) {
    // get the current from frontier
    Node curr = frontier.top();
    frontier.pop();
    // remove the current from frontierset
    frontierSet.erase(curr.p);
    // mark current as visited
    visited[curr.p] = true;
    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    neighbors = getVisitables(w,curr.p);
    //add 1 distance to the accDist from the curr
    //set the heuristic distance from the neighbor to the end node


    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    for(int i=0; i < neighbors.size(); i++) {
      int neighborCost = cost(exit,neighbors[i]);
      if(neighborCost <= leastCost) {
        leastCost = neighborCost;
        leastPoint = neighbors[i];
      }
    }
    frontier.push({leastPoint,curr.cost+1,leastCost});
    cameFrom[leastPoint] = curr.p;
    if(abs(leastPoint.x) == size || abs(leastPoint.y) == size) {
      borderExit = leastPoint;
      break;
    }
    if(borderExit != Point2D::INFINITE) {
      break;
    }

  }
    // do this up to find a visitable border and break the loop

  if(borderExit == Point2D::INFINITE)
    {
    return std::vector<Point2D>();
  }
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  std::vector<Point2D> path;
  Point2D currPoint = borderExit;
  while(currPoint != catPos) {
    path.push_back(currPoint);
    currPoint = cameFrom[currPoint];
  }
  frontierSet.clear();
  visited.clear();
  return path;
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> Agent::getVisitables(World* w, const Point2D& p)
{
  std::vector<Point2D> visitables;

  if(!visited[w->NE(p)] && !w->getContent(w->NE(p))) {
    visitables.push_back(w->NE(p));
  }
  if(!visited[w->E(p)]&& !w->getContent(w->E(p))) {
    visitables.push_back(w->E(p));
  }

  if(!visited[w->SE(p)]&& !w->getContent(w->SE(p))) {
    visitables.push_back(w->SE(p));
  }
  if(!visited[w->SW(p)]&& !w->getContent(w->SW(p))) {
    visitables.push_back(w->SW(p));
  }
  if(!visited[w->W(p)]&& !w->getContent(w->W(p))) {
    visitables.push_back(w->W(p));
  }
  if(!visited[w->NW(p)]&& !w->getContent(w->NW(p))&& cameFrom.find(w->SW(p)) == cameFrom.end()) {
    visitables.push_back(w->NW(p));
  }
  return visitables;

}

Point2D Agent::probableExit(const Point2D& p,World* w) {

  auto halfSize = w->getWorldSideSize() / 2;
  Point2D searchExit = p;
  //Few exceptions
  if(p.x == 0) {
    if(p.y < 0) {
      return {p.x,-halfSize};
    }
    if(p.y > 0)
      return {p.x, halfSize};
  }
  if(p.y == 0) {
    if(p.x < 0)
    return {-halfSize,p.y};
    if(p.x > 0)
      return {halfSize, p.y};
  }


  ////Top left
  if(p.x < 0 && p.y < 0)
  {
    if(abs(p.x) > abs(p.y))
      return {-halfSize, p.y};
    return {p.x,-halfSize};
  }
////////////Top right
  if(p.x > 0 && p.y < 0) {
    if(abs(p.x) > abs(p.y))
        return {halfSize, p.y};
      return {p.x, -halfSize};
  }
  ///////////Bottom right
  if(p.x > 0 && p.y > 0) {
    if(abs(p.x) > abs(p.y))
      return {halfSize, p.y};
      return {p.x,halfSize};
  }
  //////////////Bottom left
  if(p.x < 0 && p.y > 0) {
    if(abs(p.x) > abs(p.y))
        return {-halfSize, p.y};
        return {p.x,halfSize};
  }
  return {0,0};
}

int Agent::cost(Point2D p1, Point2D p2) {
  int c = sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2));
  return c;
}
