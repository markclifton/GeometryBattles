#pragma once

#include "ps/ecs/isystem.h"
#include "ps/utils/keyhandler.h"

#include "glm/vec3.hpp"

class InputControlSystem : public ps::ecs::ISystem, ps::utils::KeyHandler
{
public:
    InputControlSystem();
    void update(std::vector<ps::ecs::COMP_TYPE> componentsToUse, float, void** component) override;

protected:
    void process(int key, int scancode, int action, int mods) override;

private:
    glm::vec3 keyboardMovement_ {glm::vec3(0,0,0) };
};
