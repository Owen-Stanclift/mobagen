#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f separatingForce = Vector2f::zero();
  float desiredDistance = desiredMinimalDistance;
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  for (auto n : neighborhood)
  {
    Vector2f dir =  boid->transform.position - n->transform.position;
    float dist = dir.getMagnitude();
    if(dist <= desiredDistance && dist > 0) {
      Vector2f hat = dir.normalized();
      separatingForce += hat/dist;
    }
  }

  return separatingForce*desiredDistance;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
