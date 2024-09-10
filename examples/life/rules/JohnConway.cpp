#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for(int i = 0; i < world.SideSize(); i++) {
    for(int j = 0; j < world.SideSize(); j++) {

    }
  }
  //world.SetNext()
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int acc = 0;
  for(int i = -1; i <1; i++) {
    for(int j = -1; j <1; j++) {
      Point2D point = point + Point2D(i, j);
      acc += world.Get(point);
    }
    return acc;
  }
}
