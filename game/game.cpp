#include "game.h"

#include <iostream>

#include "ps/ecs/ecsmanager.h"
#include "ps/ecs/systems/renderingsystem.h"
#include "ps/managers/windowmanager.h"

#include "levels/sandbox.h"

GeometryBattles::GeometryBattles()
{
    ps::managers::WindowManager::Get().setTitle("Geometry Battles!");
    setup();
}

GeometryBattles::~GeometryBattles()
{
    ps::managers::WindowManager::Get().close();
}

void GeometryBattles::setup()
{
    contextManager_.addContext(Sandbox::CONTEXT_NAME, std::make_unique<Sandbox>());
    auto sandbox = contextManager_.find(Sandbox::CONTEXT_NAME);
    sandbox->loadResources();

    ps::ecs::ECSManager::get().addSystem(0, std::make_shared<ps::ecs::RenderingSystem>());
    contextManager_.setContext(Sandbox::CONTEXT_NAME);
}
