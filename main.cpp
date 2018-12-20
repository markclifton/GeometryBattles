#include "game/game.h"

#include "ps/managers/shadermanager.h"
#include "ps/managers/texturemanager.h"
#include "ps/managers/windowmanager.h"

int main()
{
    GeometryBattles game;
    game.run();
    ps::managers::WindowManager::Get().close();
    return 0;
}
