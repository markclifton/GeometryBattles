#pragma once

#include "ps/ecs/isystem.h"

class InteractionSystem : public ps::ecs::ISystem
{
public:
    InteractionSystem();
    void update(std::vector<ps::ecs::COMP_TYPE> componentsToUse, float, void** component) override;
};
