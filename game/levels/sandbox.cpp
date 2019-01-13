#include "sandbox.h"

#include <unistd.h>
#include <iostream>

#include "ps/managers/shadermanager.h"
#include "ps/drawable/triangle.h"
#include "ps/drawable/rectangle.h"
#include "ps/ecs/ecsmanager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "ps/managers/soundmanager.h"

#include "ps/ecs/components/inputcomponent.h"
#include "ps/ecs/components/movementcomponent.h"

std::string Sandbox::CONTEXT_NAME = "Sandbox";

Sandbox::Sandbox()
{
}

void Sandbox::run()
{
    auto s = ps::ShaderManager::Get().getShader("Base");
    s->bind();
    s->setUniform("projection", glm::mat4(1.));
    s->setUniform("view", glm::mat4(1.));
    s->setUniform("camera", glm::mat4(1.));

    ps::ECSManager::get().updateSystems(CONTEXT_NAME, {ps::InputComponent::Type, ps::MovementComponent::Type});
    ps::ECSManager::get().updateSystems(CONTEXT_NAME, {ps::VertexComponent::Type, ps::MovementComponent::Type});
    ps::ECSManager::get().updateSystems(CONTEXT_NAME, {ps::VertexComponent::Type, ps::ShaderComponent::Type});
}

void Sandbox::loadResources()
{
    ps::ShaderManager::Get().loadShader("Base", "resources/shaders/basic.vs", "resources/shaders/basic.fs");

    auto tri = std::make_shared<ps::drawable::Triangle>(CONTEXT_NAME, glm::vec3(0,0,-1), ps::ShaderManager::Get().getShader("Base"));
    //ps::ECSManager::get().addEntity(tri);

    auto rect = std::make_shared<ps::drawable::Rectangle>(CONTEXT_NAME, glm::vec3(0,0,-1), ps::ShaderManager::Get().getShader("Base"));
    rect->setColor(glm::vec4(1,1,1,1));
    //rect->setTransform(glm::scale(glm::vec3(.05,.05,.05)));

    ps::MovementComponent movement;
    rect->AddComponentOfType(ps::MovementComponent::Type, ps::MovementComponent::CreationFN(rect.get(), &movement));

    ps::InputComponent inputComponent;
    rect->AddComponentOfType(ps::InputComponent::Type, ps::InputComponent::CreationFN(rect.get(), &inputComponent));

    ps::ECSManager::get().addEntity(rect);

    ps::SoundManager::Get().loadSound("Rain", "resources/sounds/rain.mp3");
    //ps::SoundManager::Get().playSound("Rain");
}
