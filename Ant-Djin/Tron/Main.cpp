


#include "Minigin.h"
#include "TronGame.h"

int main()
{
    dae::Minigin engine{new TronGame()};
    engine.Run();
    return 0;
}

