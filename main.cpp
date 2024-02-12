#include "Game.h"

int main() {
	Game game; 
	while (game.isGameRunning())
	{
		game.update(); 
		game.render(); 
	}
}