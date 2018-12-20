#pragma once

#include "ps/contexts/context.h"

class Sandbox : public ps::ContextBase
{
public:
    Sandbox();
    void run() override;
    void loadResources() override;
};
