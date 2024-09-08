#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  for (auto n : neighborhood)
    {
    Vector2f distance = n->getPosition() - boid->getPosition();
    if(distance.getMagnitude() <= boid->getDetectionRadius()) {
      averageVelocity.x += n->velocity.x;
      averageVelocity.y += n->velocity.y;
    }
  }


  if(neighborhood.size() == 0) {
return averageVelocity;
  }
  averageVelocity.x /= neighborhood.size();
  averageVelocity.y /= neighborhood.size();
  return Vector2f::normalized(averageVelocity);
}