#include "CohesionRule.h"

#include "../../../cmake-build-debug/_deps/glm-src/glm/detail/func_geometric.inl"
#include "../gameobjects/Boid.h"
#include "math/Point2D.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f centerMass;
  if(neighborhood.size() == 0) {
    return {0,0};
  }
  else {
    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    for (auto n : neighborhood)
    {
      if(n->transform.position.x == boid->transform.position.x && n->transform.position.y == boid->transform.position.y)
        continue;
      centerMass = n->transform.position/neighborhood.size();
      Vector2f length = centerMass - boid->transform.position;
      float magnitude = sqrt(length.x * length.x + length.y * length.y);
      if(magnitude <= radius) {
        cohesionForce = length/radius;
        return cohesionForce;
      }
      if(magnitude > radius) {
        return cohesionForce;
      }
      // find center of mass
      return cohesionForce;
    }
  }
}