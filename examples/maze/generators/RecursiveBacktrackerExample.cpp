#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <algorithm>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> visitPoints = getVisitables(w,currentPoint);
    int randNum = 0;
  int distX = 0;
  int distY = 0;
    std::mt19937 rng = std::mt19937(std::random_device()());
    std::uniform_int_distribution<int> range(0,99);
    randNum = range(rng);

  if(stack.empty() && !visited[-sideOver2][-sideOver2]) {
    currentPoint = {-sideOver2, -sideOver2};
    stack.push_back(currentPoint);
  }
  else {
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
      w->SetNodeColor(currentPoint,Color::Green);
      if(w->GetNodeColor(stack.back()) != Color::Black) {
        w->SetNodeColor((stack.back()), Color::Red);
      }
      else {
        w->SetNodeColor(stack.back(), Color::Black);
      }
    }
    else {
      w->SetNodeColor(currentPoint,Color::Black);
      w->SetNodeColor((stack.back()), Color::Green);
      w->SetNode(stack.back(),w->GetNode(currentPoint));
      currentPoint = stack.back();
      stack.pop_back();
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
  std::vector<Point2D>::iterator it;
  if(w->GetNorth(p) && p.y > -sideOver2) {
      it = find(stack.begin(),stack.end(),p.Up());
      if(it == stack.end()&& !visited[p.Up().y][p.Up().x]) {
        visitables.push_back(p.Up());
      }
  }
  if(w->GetEast(p) && p.x < sideOver2) {
      it = find(stack.begin(),stack.end(),p.Right());
      if(it == stack.end() && !visited[p.Right().y][p.Right().x]) {
        visitables.push_back(p.Right());

      }
  }
  if(w->GetSouth(p) && p.y < sideOver2) {
      it = find(stack.begin(),stack.end(),p.Down());
      if(it == stack.end()&& !visited[p.Down().y][p.Down().x]) {
        visitables.push_back(p.Down());

      }
  }
  if(w->GetWest(p) && p.x > -sideOver2) {
      it = find(stack.begin(),stack.end(),p.Left());
      if(it == stack.end() && !visited[p.Left().y][p.Left().x]) {
        visitables.push_back(p.Left());

      }
  }
  // todo: implement this

  return visitables;
}
