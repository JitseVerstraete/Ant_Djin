#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BurgerTimeGame.h"
#include "Minigin.h"

int main(int, char* []) {
	dae::Minigin engine{ new BurgerTimeGame()};
	engine.Run();
	return 0;
}