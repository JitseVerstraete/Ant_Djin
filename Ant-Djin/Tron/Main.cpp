#include "Minigin.h"
#include "TronGame.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

int main()
{
    dae::Minigin engine{new TronGame(), 640, 680};
    engine.Run();
    return 0;
}

