#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "Sprite.h"
#include "Message.h"
#include "Component.h"
#include "Entity.h"
#include "GraphicsEngine.h"
#include "Game.h"
#include "InputManager.h"
#include "Global.h"

#define P_KEY 80
#define SPACE_BAR 32
#define ESC_KEY 27

#define PLAYER_MOVEMENT 10.0f

void CInputManager::processInput() {
	if (!game->getPaused()) {
		// Character movement
		if (SYS_KeyPressed(SYS_KEY_LEFT)) {
			game->movePlayer(PLAYER_MOVEMENT, CSprite::EOrientation::left);
		}
		else if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
			game->movePlayer(PLAYER_MOVEMENT, CSprite::EOrientation::right);
		}

		// Shot
		if (SYS_KeyPressed(SPACE_BAR) && !game->getSpacePressed()) {
			game->createBullet();
		}

		// Pause the game
		if (SYS_KeyPressed(P_KEY) && !game->getPKeyPressed())
		{
			if (game->getPaused())
			{
				game->setPaused(false);
			}
			else
			{
				game->setPaused(true);
			}
		}

		// Controll space bar press
		if (SYS_KeyPressed(SPACE_BAR))
		{
			game->setSpacePressed(true);
		}
		else
		{
			game->setSpacePressed(false);
		}

		// Controll P key press
		if (SYS_KeyPressed(P_KEY))
		{
			game->setPKeyPressed(true);
		}
		else
		{
			game->setPKeyPressed(false);
		}
	}
	else {
		game->usePauseMenuInput();
	}
}