#pragma once

#include <string>
#include "ps/contexts/context.h"

#include "ps/drawable/renderers/batch.h"

class Sandbox : public ps::ContextBase
{
public:
    Sandbox();
    void run() override;
    void loadResources() override;

    static std::string CONTEXT_NAME;

private:
    std::unique_ptr<ps::drawable::renderer::Batch> batch_;
};
