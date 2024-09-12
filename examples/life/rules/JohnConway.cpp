#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for(int i = 0; i < world.SideSize(); i++) {
    for(int j = 0; j < world.SideSize(); j++) {
      Point2D point =  Point2D(i, j);

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
  //world.SetNext()
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int acc = 0;
  for(int i = -1; i <2; i++)
    {
    for(int j = -1; j <2; j++)
      {
      Point2D checkPoint = Point2D(point.x+i, point.y+j);
      if(point.x+i >= 0 && point.x+i < world.SideSize()-1 && point.y+j >= 0 && point.y+j < world.SideSize())
      acc += world.Get(checkPoint);
    }
  }
  return acc;
}
