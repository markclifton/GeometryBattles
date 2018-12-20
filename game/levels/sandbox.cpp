#include "sandbox.h"

#include <unistd.h>
#include <iostream>

#include "ps/managers/shadermanager.h"
#include "ps/drawable/triangle.h"
#include "ps/ecs/ecsmanager.h"

std::string Sandbox::CONTEXT_NAME = "Sandbox";

Sandbox::Sandbox()
{
}

void Sandbox::run()
{
    std::cout << "Running Sandbox!" << std::endl;
    sleep(1);

    auto s = ps::managers::ShaderManager::Get().getShader("Base");
    s->bind();
    s->setUniform("projection", glm::mat4(1.));
    s->setUniform("view", glm::mat4(1.));
    s->setUniform("camera", glm::mat4(1.));

    ps::ecs::ECSManager::get().updateSystems(CONTEXT_NAME, {ps::VertexComponent::Type, ps::ShaderComponent::Type});
}

void Sandbox::loadResources()
{
    ps::managers::ShaderManager::Get().loadShader("Base", "resources/shaders/basic.vs", "resources/shaders/basic.fs");

    auto tri = std::make_shared<ps::drawable::Triangle>(CONTEXT_NAME, glm::vec3(0,0,-1), ps::managers::ShaderManager::Get().getShader("Base"));
    ps::ecs::ECSManager::get().addEntity(tri);
}
