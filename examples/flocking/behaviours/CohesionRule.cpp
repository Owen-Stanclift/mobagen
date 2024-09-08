#include "CohesionRule.h"

#include "../../../cmake-build-debug/_deps/glm-src/glm/detail/func_geometric.inl"
#include "../gameobjects/Boid.h"
#include "math/Point2D.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f centerMass = Vector2f::zero();
  Vector2f centerPosition = Vector2f::zero();
  int neightborCount = 0;
  if(neighborhood.size() == 0) {
    return {0,0};
  }
  else {
    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    for (auto n : neighborhood) {
      Vector2f length = n->transform.position - boid->transform.position;
      float distance =  length.getMagnitude();
      if(distance <= boid->getDetectionRadius())
        {
        neightborCount++;
        centerPosition += n->transform.position;
      }
    }
    if(neightborCount > 0)
    {
      centerMass = centerPosition/neightborCount; //PCM
      Vector2f forceLength = centerMass - boid->transform.position; // ->BoidPCM
      float magnitude = forceLength.getMagnitude(); // |Boid PCM|
      if(magnitude <= boid->getDetectionRadius())
        {
        cohesionForce =  forceLength/boid->getDetectionRadius();
        return cohesionForce;
      }
      if(magnitude > boid->getDetectionRadius()) {
        return Vector2f::zero();
      }
    }
    else
      return Vector2f::zero();
  }
}