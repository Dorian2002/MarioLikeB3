#include <iostream>
#include <engine/GameEngine.h>
int main()
{
	bool success = true;
	GameEngine* game = GameEngine::GetInstance();
	success = game->RunMenu();
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}