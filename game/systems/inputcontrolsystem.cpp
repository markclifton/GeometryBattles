#include "inputcontrolsystem.h"

#include "game/components/inputcomponent.h"
#include "game/components/movementcomponent.h"
#include "ps/ecs/entities/drawableentity.h"
#include "ps/managers/windowmanager.h"

#include <GLFW/glfw3.h>

InputControlSystem::InputControlSystem()
{
    components_.push_back(InputComponent::Type);;
    multithreaded_ = false;

    ps::WindowManager::Get().registerHandler(this);
}

void InputControlSystem::update(std::vector<ps::ecs::COMP_TYPE>, float, void* component)
{
    auto baseComponent = static_cast<ps::ecs::BaseComponent*>(component);
    auto entity = static_cast<ps::drawable::DrawableEntity*>(baseComponent->entityHandle);
    auto movement = static_cast<MovementComponent*>(entity->GetComponentByTypeAndIndex(MovementComponent::Type, 0));

    movement->speed = keyboardMovement_;
}

void InputControlSystem::process(int key, int /*scancode*/, int action, int /*mods*/)
{
    switch (key)
    {
    case GLFW_KEY_W:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.y += .005f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.y -= .005f;
        }
        break;
    case GLFW_KEY_S:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.y -= .005f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.y += .005f;
        }
        break;
    case GLFW_KEY_A:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.x -= .005f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.x += .005f;
        }
        break;
    case GLFW_KEY_D:
        if(action == GLFW_PRESS)
        {
            keyboardMovement_.x += .005f;
        }
        else if(action == GLFW_RELEASE)
        {
            keyboardMovement_.x -= .005f;
        }
        break;
    }
}
