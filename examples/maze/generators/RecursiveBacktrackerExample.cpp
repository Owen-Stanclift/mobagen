#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
    std::vector<Point2D> visitPoints = getVisitables(w,currentPoint);
    int randNum = 0;
  int distX = 0;
  int distY = 0;
    std::mt19937 rng = std::mt19937(std::random_device()());
    std::uniform_int_distribution<int> range(0,99);
    randNum = range(rng);

  if(visitPoints.size() > 0) {
    switch(randNum % visitPoints.size()) {
      case 0:
      stack.push_back(currentPoint);
      w->SetNode(visitPoints.at(0),w->GetNode(currentPoint));
      distX = visitPoints.at(0).x - currentPoint.x;
      distY = visitPoints.at(0).y - currentPoint.y;
      currentPoint = { currentPoint.x + distX ,currentPoint.y +distY };
      visited[currentPoint.y][currentPoint.x] = true;
      break;
      case 1:
      stack.push_back(currentPoint);
      w->SetNode(visitPoints.at(1),w->GetNode(currentPoint));
      distX = visitPoints.at(1).x - currentPoint.x;
      distY = visitPoints.at(1).y - currentPoint.y;
      currentPoint = { currentPoint.x + distX ,currentPoint.y +distY };
      visited[currentPoint.y][currentPoint.x] = true;
      break;
      case 2:
      stack.push_back(currentPoint);
      w->SetNode(visitPoints.at(2),w->GetNode(currentPoint));
      distX = visitPoints.at(2).x - currentPoint.x;
      distY = visitPoints.at(2).y - currentPoint.y;
      currentPoint = { currentPoint.x + distX ,currentPoint.y +distY };
      visited[currentPoint.y][currentPoint.x] = true;
      break;
      case 3:
      stack.push_back(currentPoint);
      w->SetNode(visitPoints.at(3),w->GetNode(currentPoint));
      distX = visitPoints.at(3).x - currentPoint.x;
      distY = visitPoints.at(3).y - currentPoint.y;
      currentPoint = { currentPoint.x + distX ,currentPoint.y +distY };
      visited[currentPoint.y][currentPoint.x] = true;
      break;

    }
  }
  else {
    w->SetNode(stack.back(),w->GetNode(currentPoint));
    currentPoint = stack.back();
    stack.pop_back();
    }


  if(w->GetNodeColor(currentPoint) == Color::DarkGray) {
    w->SetNodeColor(currentPoint,Color::Red);
  }
  else {
    if(w->GetNodeColor(currentPoint) == Color::Red) {
      w->SetNodeColor(currentPoint,Color::Black);
    }
  }
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  if(w->GetNorth(p) && p.y > -sideOver2) {
    if(!visited[p.y-1][p.x])
    visitables.push_back(p.Up());
  }
  if(w->GetEast(p) && p.x < sideOver2) {
    if(!visited[p.y][p.x+1])
    visitables.push_back(p.Right());
  }
  if(w->GetSouth(p) && p.y < sideOver2) {
    if(!visited[p.y+1][p.x])
    visitables.push_back(p.Down());
  }
  if(w->GetWest(p) && p.x > -sideOver2) {
    if(!visited[p.y][p.x-1])
    visitables.push_back(p.Left());
  }
  // todo: implement this

  return visitables;
}
