#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

#include <map>
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
   // use .at() to get data, if the element dont exist [] will give you wrong results
  std::queue<Point2D> frontier;                   // to store next ones to visit
  std::unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  auto size = w->getWorldSideSize()/2;
  std::vector<Point2D> neighbors;
  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D curr = frontier.front();
    frontier.pop();
    // remove the current from frontierset
    frontierSet.erase(curr);
    // mark current as visited
    visited[curr] = true;
    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    neighbors = getVisitables(w,curr);

    //add 1 distance to the accDist from the curr
    //set the heuristic distance from the neighbor to the end node


    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    for(int i=0; i < neighbors.size(); i++) {
      frontier.push(neighbors[i]);
      frontierSet.insert(neighbors[i]);
      if(abs(neighbors[i].x) == size || abs(neighbors[i].y) == size) {
        borderExit = neighbors[i];
        break;
      }
    }

    if(borderExit != Point2D::INFINITE) {
      break;
    }
    // do this up to find a visitable border and break the loop
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
    cameFrom[w->NE(p)] = p;
  }
  if(!visited[w->E(p)]&& !w->getContent(w->E(p))) {
    visitables.push_back(w->E(p));
    cameFrom[w->E(p)] = p;
  }

  if(!visited[w->SE(p)]&& !w->getContent(w->SE(p))) {
    visitables.push_back(w->SE(p));
    cameFrom[w->SE(p)] = p;
  }
  if(!visited[w->SW(p)]&& !w->getContent(w->SW(p))) {
    visitables.push_back(w->SW(p));
    cameFrom[w->SW(p)] = p;
  }
  if(!visited[w->W(p)]&& !w->getContent(w->W(p))) {
    visitables.push_back(w->W(p));
    cameFrom[w->W(p)] = p;
  }
  if(!visited[w->NW(p)]&& !w->getContent(w->NW(p))) {
    visitables.push_back(w->NW(p));
    cameFrom[w->NW(p)] = p;
  }
  return visitables;

}

Point2D Agent::probableExit(const Point2D& p,World* w) {

  auto halfSize = w->getWorldSideSize() / 2;
  ////Top left
  if(p.x < 0 && p.y < 0 && abs(p.x) > abs(p.y)) {
    return {-halfSize, p.y};
  }
  if(p.x < 0 && p.y < 0 && abs(p.x) < abs(p.y)) {
    return {p.x, -halfSize};
  }
////////////Top right
  if(p.x > 0 && p.y < 0 && abs(p.x) > abs(p.y)) {
    return {halfSize, p.y};
  }
  if(p.x > 0 && p.y < 0 && abs(p.x) < abs(p.y)) {
    return {p.x, -halfSize};
  }
  ///////////Bottom right
  if(p.x > 0 && p.y > 0 && abs(p.x) > abs(p.y)) {
    return {halfSize, p.y};
  }
  if(p.x > 0 && p.y > 0 && abs(p.x) < abs(p.y)) {
    return {p.x, halfSize};
  }
  //////////////Bottom left
  if(p.x < 0 && p.y > 0 && abs(p.x) > abs(p.y)) {
    return {-halfSize, p.y};
  }
  if(p.x < 0 && p.y > 0 && abs(p.x) < abs(p.y)) {
    return {p.x, halfSize};
  }

  return {0,0};
}
