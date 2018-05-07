#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "ItemSelectable.h"
#include "Menu.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "Sprite.h"
#include "Message.h"
#include "Component.h"
#include "Entity.h"
#include "InputManager.h"
#include "GraphicsEngine.h"
#include "AppManager.h"
#include "Game.h"
#include "Global.h"

using namespace rapidjson;
using namespace std;

CModeAppGame::CModeAppGame() {
	inputManager     = new CInputManager   ();
	graphicsEngine   = new CGraphicsEngine ();

	mActualMenu = nullptr;
}

CModeAppGame::~CModeAppGame() {
	delete inputManager;
	inputManager = nullptr;
	
	delete graphicsEngine;
	graphicsEngine = nullptr;

	delete mActualMenu;
	mActualMenu = nullptr;
}

void CModeAppGame::setActualMenu(CMenu* menu) {
	if (menu) {
		delete mActualMenu;
		mActualMenu = nullptr;

		mActualMenu = menu;
	}
	else {
		game->setPaused(false);

		delete mActualMenu;
		mActualMenu = nullptr;
	}
}

CMenu* CModeAppGame::getActualMenu() const {
	return mActualMenu;
}

void CModeAppGame::input() {
	if (inputManager) {
		inputManager->processInput();
	}
}

void CModeAppGame::run() {
	if (game) {
		game->run();
	}
}

void CModeAppGame::render() {
	if (graphicsEngine && !mActualMenu) {
		graphicsEngine->render();
	}
	else if (mActualMenu) {
		mActualMenu->render();
	}
}

void CModeAppGame::NotifyActivation() {
	if (!game) {
		CAppManager::gameLevel level = appManager->getGameLevel();

		ifstream ifs("data/levels.json");
		IStreamWrapper isw(ifs);
		Document d;
		d.ParseStream(isw);

		int enemies = 0;

		// Cargo textura de personaje
		CGraphicsEngine::Texture characterTexture;
		characterTexture.mType = CSprite::character;

		// Cargo textura de bala
		CGraphicsEngine::Texture enemyTexture;
		enemyTexture.mType = CSprite::enemy;

		// Cargo textura de enemigo
		CGraphicsEngine::Texture bulletTexture;
		bulletTexture.mType = CSprite::bullet;

		if (!d.HasParseError()) {
			if (d.IsObject()) {
				switch (level) {
					case CAppManager::easyLevel:
						if (d.HasMember("levelEasy")) {
							if (d["levelEasy"].IsObject()) {
								if (d["levelEasy"].HasMember("level")) {
									if (d["levelEasy"]["enemies"].IsInt()) {
										enemies = d["levelEasy"]["enemies"].GetInt();
									}
									else {
										appManager->setLevelsError(true);
									}
								}
								else {
									appManager->setLevelsError(true);
								}
							}
							else {
								appManager->setLevelsError(true);
							}
						}
						else {
							appManager->setLevelsError(true);
						}
						break;
					case CAppManager::midLevel:
						if (d.HasMember("levelMid")) {
							if (d["levelMid"].IsObject()) {
								if (d["levelMid"].HasMember("level")) {
									if (d["levelMid"]["enemies"].IsInt()) {
										enemies = d["levelMid"]["enemies"].GetInt();
									}
									else {
										appManager->setLevelsError(true);
									}
								}
								else {
									appManager->setLevelsError(true);
								}
							}
							else {
								appManager->setLevelsError(true);
							}
						}
						else {
							appManager->setLevelsError(true);
						}
						break;
					case CAppManager::hardLevel:
						if (d.HasMember("levelHard")) {
							if (d["levelHard"].IsObject()) {
								if (d["levelHard"].HasMember("level")) {
									if (d["levelHard"]["enemies"].IsInt()) {
										enemies = d["levelHard"]["enemies"].GetInt();
									}
									else {
										appManager->setLevelsError(true);
									}
								}
								else {
									appManager->setLevelsError(true);
								}
							}
							else {
								appManager->setLevelsError(true);
							}
						}
						else {
							appManager->setLevelsError(true);
						}
						break;
				}

				if (d.HasMember("levelTextures")) {
					if (d["levelTextures"].IsObject()) {
						if (d["levelTextures"].HasMember("characterTexture") && 
							d["levelTextures"].HasMember("enemyTexture") && 
							d["levelTextures"].HasMember("bulletTexture")) {

							characterTexture.mTextureId = CORE_LoadPNG(d["levelTextures"]["characterTexture"].GetString(), false);
							enemyTexture.mTextureId = CORE_LoadPNG(d["levelTextures"]["enemyTexture"].GetString(), false);
							bulletTexture.mTextureId = CORE_LoadPNG(d["levelTextures"]["bulletTexture"].GetString(), false);
						}
						else {
							appManager->setLevelsError(true);
						}
					}
					else {
						appManager->setLevelsError(true);
					}
				}
				else {
					appManager->setLevelsError(true);
				}
			}
			else {
				appManager->setLevelsError(true);
			}
		}
		else {
			appManager->setLevelsError(true);
		}

		graphicsEngine->setNumEnemies(enemies);

		graphicsEngine->addTexture(characterTexture);
		graphicsEngine->addTexture(enemyTexture);
		graphicsEngine->addTexture(bulletTexture);

		game = new CGame();
	}
}

void CModeAppGame::NotifyDeactivation() {
	if (game) {
		delete game;
		game = nullptr;

		appManager->setGameLevel(CAppManager::onMenu);
	}
}

Mode CModeAppGame::getId() const {
	return GameMode;
}