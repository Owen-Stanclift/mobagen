#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close


  Vector2f separatingForce = Vector2f::zero();
      float desiredDistance = desiredMinimalDistance;
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
      for (auto n : neighborhood)
        {
        Vector2f dir = n->transform.position - boid->transform.position;
        float dist = dir.getMagnitude();
        if(dist <= desiredDistance && dist > 0) {
            Vector2f hat = dir.normalized();
            separatingForce = hat/dist;
          if(separatingForce.getMagnitude() > maxForce) //Max force is 2 as no clue if it was given
            {
            Vector2f forceHat = separatingForce.normalized();
            return forceHat * maxForce;
          }
          else {
            return separatingForce;
          }
        }
        else {
          return Vector2f::zero();
        }
      }

     if (!neighborhood.empty()) {
         Vector2f position = boid->transform.position;
         int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
       separatingForce = (separatingForce);

      }



  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
