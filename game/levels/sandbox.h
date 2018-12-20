#pragma once

#include <string>
#include "ps/contexts/context.h"

class Sandbox : public ps::ContextBase
{
public:
    Sandbox();
    void run() override;
    void loadResources() override;

    static std::string CONTEXT_NAME;
};
