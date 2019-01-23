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
    multithreaded_ = false;
}

void MovementSystem::update(std::vector<COMP_TYPE>, float, void* component)
{
    auto baseComponent = static_cast<BaseComponent*>(component);
    auto entity = static_cast<drawable::DrawableEntity*>(baseComponent->entityHandle);

    auto transform = entity->getTransform();
    auto movement = static_cast<MovementComponent*>(entity->GetComponentByTypeAndIndex(MovementComponent::Type, 0));

    if(movement->speed == glm::vec3(0))
    {
        return;
    }

    transform *= glm::translate(movement->speed);
    entity->setTransform(transform);
}
}
}
