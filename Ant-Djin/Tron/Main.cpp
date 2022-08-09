#include "Minigin.h"
#include "TronGame.h"

int main()
{
    dae::Minigin engine{new TronGame(), 640, 740};
    engine.Run();
    return 0;
}

