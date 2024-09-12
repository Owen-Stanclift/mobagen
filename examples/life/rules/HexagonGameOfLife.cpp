//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  for(int i = 0; i < world.SideSize(); i++) {
    for(int j = 0; j < world.SideSize(); j++) {
      Point2D point = Point2D(i, j);

      if(world.Get(point))
      {
        if(CountNeighbors(world, point) < 2)
          world.SetNext(point,false);
        if(CountNeighbors(world, point) >= 2 && CountNeighbors(world, point) < 4)
          world.SetNext(point,true);
        if(CountNeighbors(world, point) >3)
          world.SetNext(point,false);
      }
      else
        if(CountNeighbors(world,point) == 3)
          world.SetNext(point,true);
    }
  }
}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int acc = 0;
  for(int j = -1; j < 2; j++) {
    if(j == 0) {
      Point2D checkPoint = Point2D(point.x-1, point.y);
      if(point.x -1 >= 0)
      acc += world.Get(checkPoint);
      checkPoint = Point2D(point.x+1, point.y);
      if(point.x +1 < world.SideSize())
      acc += world.Get(checkPoint);
    }
    else if(point.y +j%2 == 0) {
      Point2D checkPoint = Point2D(point.x,  point.y+j);
      if(point.y +j < world.SideSize() && point.y+j >= 0)
      acc += world.Get(checkPoint);
      checkPoint = Point2D(point.x+1,  point.y+j);
      if(point.x +1 < world.SideSize() && point.y +j < world.SideSize() && point.y+j >=0)
      acc += world.Get(checkPoint);
    }
    else {
      Point2D checkPoint = Point2D(point.x-1,  point.y+j);
      if(point.x -1 >= 0 && point.y +j < world.SideSize() && point.y+j >=0)
      acc += world.Get(checkPoint);
      checkPoint = Point2D(point.x,  point.y+j);
      if(point.y +j < world.SideSize() && point.y+j >= 0)
      acc += world.Get(checkPoint);
    }
  }

  return acc;
}
