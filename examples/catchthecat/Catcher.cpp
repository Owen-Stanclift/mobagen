#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    auto cat = world->getCat();
    Point2D exitPoint = probableExit(cat,world);
    if (cat.x != exitPoint.x && cat.y != exitPoint.y && !world->getContent(exitPoint)) {return exitPoint;}
  }
}
