#include "Controller2048.h"

void Controller2048::update()
{
	if (KeyUp.down()) logic->moveUp();
	else if (KeyDown.down()) logic->moveDown();
	else if (KeyRight.down()) logic->moveRight();
	else if (KeyLeft.down()) logic->moveLeft();

	if (KeyR.down()) {
		logic->initBoard();
	}
}
