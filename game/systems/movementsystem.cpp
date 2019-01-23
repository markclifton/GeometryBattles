#include "movementsystem.h"

#include "game/components/movementcomponent.h"
#include "ps/ecs/components/vertexcomponent.h"

#include "ps/ecs/entities/drawableentity.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include <iostream>
namespace ps
{
namespace ecs
{
MovementSystem::MovementSystem()
{
    components_.push_back(MovementComponent::Type);
    multithreaded_ = true;
}

void MovementSystem::update(std::vector<COMP_TYPE>, float, void** component)
{
    auto baseComponent = reinterpret_cast<BaseComponent*>(*component);
    auto entity = reinterpret_cast<drawable::DrawableEntity*>(baseComponent->entityHandle);

    auto transform = entity->getTransform();
    auto movement = reinterpret_cast<MovementComponent*>(entity->GetComponentByTypeAndIndex(MovementComponent::Type, 0));

    transform *= glm::translate(movement->speed);
    entity->setTransform(transform);
}
}
}
