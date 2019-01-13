#include "inputcontrolsystem.h"

#include "ps/ecs/components/inputcomponent.h"
#include "ps/ecs/components/movementcomponent.h"
#include "ps/ecs/ientity.h"
#include "ps/managers/windowmanager.h"

#include <GLFW/glfw3.h>

namespace ps
{
namespace ecs
{
InputControlSystem::InputControlSystem()
{
    components_.push_back(InputComponent::Type);
    components_.push_back(MovementComponent::Type);

    WindowManager::Get().registerHandler(this);
}

void InputControlSystem::update(std::vector<COMP_TYPE>, float, void** component)
{
    auto baseComponent = reinterpret_cast<BaseComponent*>(*component);
    auto entity = reinterpret_cast<ecs::IEntity*>(baseComponent->entityHandle);
    auto movement = reinterpret_cast<MovementComponent*>(entity->GetComponentByTypeAndIndex(MovementComponent::Type, 0));

    movement->speed = keyboardMovement_;
}

void InputControlSystem::process(int key, int /*scancode*/, int action, int /*mods*/)
{
    switch (key)
    {
    case GLFW_KEY_W:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.x += .001f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.x -= .001f;
        }
        break;
    case GLFW_KEY_S:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.x -= .001f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.x += .001f;
        }
        break;
    case GLFW_KEY_A:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.y -= .001f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.y += .001f;
        }
        break;
    case GLFW_KEY_D:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.y += .001f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.y -= .001f;
        }
        break;
    }
}
}
}
