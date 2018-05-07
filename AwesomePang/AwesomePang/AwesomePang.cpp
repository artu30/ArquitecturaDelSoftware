#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "ItemSelectable.h"
#include "Menu.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Message.h"
#include "Component.h"
#include "Entity.h"
#include "GraphicsEngine.h"
#include "AppManager.h"
#include "Game.h"
#include "Global.h"
#include <vld.h>

// Application manager attr
CAppManager* appManager = nullptr;

// Game attr
CGame* game = nullptr;

// Graphics Engine attr
CGraphicsEngine* graphicsEngine = nullptr;

// Input manager attr
CInputManager* inputManager = nullptr;

int Main() {
	FONT_Init();

	// Up render sistem
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClearColor(0.0f, 0.1f, 0.3f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	appManager = new CAppManager();

	while (!SYS_GottaQuit()) {
		// Manage actual & wanted mode
		appManager->manageMode();

		// Process input, logic and render
		appManager->processInput();
		appManager->run();
		appManager->render();

		// Keep working
		SYS_Pump();
		SYS_Sleep(17);
	}

	FONT_End();

	delete appManager;
	appManager = nullptr;

	delete game;
	game = nullptr;

	delete inputManager;
	inputManager = nullptr;

	delete graphicsEngine;
	graphicsEngine = nullptr;

    return 0;
}

