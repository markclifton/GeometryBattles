#include "interactionsystem.h"

#include "ps/ecs/ecsmanager.h"
#include "ps/ecs/entities/drawableentity.h"

#include "game/components/inputcomponent.h"
#include "game/components/movementcomponent.h"
#include "game/components/interactioncomponent.h"

InteractionSystem::InteractionSystem()
{
    components_.push_back(InteractionComponent::Type);
    multithreaded_ = false;
}

void InteractionSystem::update(std::vector<ps::ecs::COMP_TYPE>, float, void* component)
{
    auto baseComponent = static_cast<ps::ecs::BaseComponent*>(component);
    auto thisEntity = static_cast<ps::drawable::DrawableEntity*>(baseComponent->entityHandle);

    for(auto& entityRaw : ps::ECSManager::get().entities_)
    {
        if(entityRaw.get() != thisEntity && entityRaw->NumComponentsForType(InputComponent::Type) > 0)
        {
            auto entity = static_cast<ps::drawable::DrawableEntity*>(entityRaw.get());

            auto thisPosition = thisEntity->getTransform() * glm::vec4(thisEntity->verts()[0].pos,1);
            auto entityPosition = entity->getTransform() * glm::vec4(entity->verts()[0].pos,1);

            auto resultVector = entityPosition - thisPosition;
            resultVector = glm::normalize(resultVector);

            auto movement = static_cast<MovementComponent*>(thisEntity->GetComponentByTypeAndIndex(MovementComponent::Type, 0));
            movement->speed = resultVector * .001f;

            return;
        }
    }
}
