#include "game.h"

#include <iostream>

#include "ps/ecs/ecsmanager.h"
#include "ps/ecs/systems/renderingsystem.h"
#include "ps/managers/windowmanager.h"

#include "levels/sandbox.h"

GeometryBattles::GeometryBattles()
{
    ps::managers::WindowManager::Get();
    setup();
}

GeometryBattles::~GeometryBattles()
{
}

void GeometryBattles::setup()
{
    contextManager_.addContext("Sandbox", std::make_unique<Sandbox>());
    auto sandbox = contextManager_.find("Sandbox");
    sandbox->loadResources();

    ps::ecs::ECSManager::get().addSystem(0, std::make_shared<ps::ecs::RenderingSystem>());
    contextManager_.setContext("Sandbox");
}
