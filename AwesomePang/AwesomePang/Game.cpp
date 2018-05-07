#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "ItemSelectable.h"
#include "Menu.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "PauseMenu.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Message.h"
#include "Component.h"
#include "Entity.h"
#include "GraphicsEngine.h"
#include "AppManager.h"
#include "Game.h"
#include "Global.h"
#include "CollisionsEngine.h"

#define MAX_BULLETS 4

CGame::CGame() {
	mPaused = false;

	// Init player
	vec2 firstPos;
	firstPos.x = SCR_WIDTH / 2;
	firstPos.y = 40;

	CEntity* characterEntity = new CEntity();
	characterEntity->setEntityType(CSprite::character);
	characterEntity->setEntitySize(CSprite::midSize);
	characterEntity->setEntityPosition(firstPos);

	CComponentRemovable* componentRemovable = new CComponentRemovable(characterEntity);
	CComponentRendereable* componentRendereable = new CComponentRendereable(characterEntity);
	
	CMessageRendereable msg;
	componentRendereable->receiveMessage(msg);
	
	characterEntity->AddComponent(componentRemovable);
	characterEntity->AddComponent(componentRendereable);

	mEntities.push_back(characterEntity);

	mPlayer = characterEntity;

	// Init enemies
	int enemiesCount = 0;
	int numEnemies = graphicsEngine->getNumEnemies();
	while (enemiesCount < numEnemies) {
		CEntity* newEnemy = new CEntity();
		newEnemy->setEntityType(CSprite::enemy);
		newEnemy->setEntitySize(CSprite::bigSize);

		CSprite::EOrientation orientation = CSprite::EOrientation::right;
		if (enemiesCount % 2 == 0) {
			orientation = CSprite::EOrientation::left;
		}
		float posInX = CSprite::bigSize * static_cast<float>(enemiesCount) + (CSprite::bigSize / 2);
		float posInY = SCR_HEIGHT - 100;

		vec2 enemyPosition;
		enemyPosition.x = posInX;
		enemyPosition.y = posInY;

		newEnemy->setEntityPosition(enemyPosition);

		CComponentElementOrientation* componentEnemyOrientation      = new CComponentElementOrientation (newEnemy);
		CComponentInertialMovement*   componentEnemyInertialMovement = new CComponentInertialMovement   (newEnemy);
		CComponentRemovable*          componentEnemyRemovable        = new CComponentRemovable          (newEnemy);
		CComponentRendereable*        componentRendereable           = new CComponentRendereable        (newEnemy);

		CMessageRendereable msg;
		componentRendereable->receiveMessage(msg);

		componentEnemyOrientation->setOrientationInX(orientation);
		componentEnemyOrientation->setOrientationInY(CSprite::EOrientation::right);

		newEnemy->AddComponent (componentEnemyOrientation      );
		newEnemy->AddComponent (componentEnemyInertialMovement );
		newEnemy->AddComponent (componentEnemyRemovable        );
		newEnemy->AddComponent (componentRendereable           );

		mEntities.push_back(newEnemy);

		enemiesCount++;
	}

	if (appManager->getLevelsError()) {
		appManager->setWantedMode(MenuMode);
	}
}

CGame::~CGame() {
	for (auto iterator = mEntities.begin(); iterator != mEntities.end(); ++iterator) {
		delete *iterator;
	}
	mEntities.clear();
}

// Get number of entities of a type
int CGame::getCountEntitiesByType(CSprite::Type type) {
	int entityCount = 0;

	for (auto entityIterator = mEntities.begin(); entityIterator < mEntities.end(); entityIterator++) {
		if ((*entityIterator)->getEntityType() == type) {
			entityCount++;
		}
	}

	return entityCount;
}

bool CGame::getSpacePressed() const {
	return mSpacePressedController;
}

bool CGame::getEscapePressed() const {
	return mEscapePressedController;
}

bool CGame::getPKeyPressed() const {
	return mPKeyPressedController;
}

void CGame::setSpacePressed(bool pressed) {
	mSpacePressedController = pressed;
}

void CGame::setEscapePressed(bool pressed) {
	mEscapePressedController = pressed;
}

void CGame::setPKeyPressed(bool pressed) {
	mPKeyPressedController = pressed;
}

bool CGame::getPaused() const {
	return mPaused;
}

void CGame::setPaused(bool paused) {
	mPaused = paused;

	CModeAppGame* actualMode = (CModeAppGame*)appManager->getAppMode();

	CPauseMenu* pauseMenu = new CPauseMenu(actualMode);
	actualMode->setActualMenu(pauseMenu);
}

void CGame::run() {
	if (!mPaused) {
		// Collision bullet - enemy
		checkCollisionBulletEnemy();

		// Collision enemy - character
		checkCollisionEnemyCharacter();

		// Move bullets and enemies
		moveElements();

		// Remove elements
		removeElements();
	}
}

void CGame::movePlayer(float xMovement, CSprite::EOrientation orientation) {
	if (orientation == CSprite::EOrientation::left) {
		if (mPlayer->getEntityPosition().x > 0 + mPlayer->getEntitySprite()->getSpriteSize() / 2) {
			vec2 newPos;
			newPos.x = mPlayer->getEntityPosition().x - xMovement;
			newPos.y = mPlayer->getEntityPosition().y;
			mPlayer->setEntityPosition(newPos);
			mPlayer->getEntitySprite()->setSpritePosition(newPos);
		}
	}
	else if (orientation == CSprite::EOrientation::right) {
		if (mPlayer->getEntityPosition().x < SCR_WIDTH - mPlayer->getEntitySprite()->getSpriteSize() / 2) {
			vec2 newPos;
			newPos.x = mPlayer->getEntityPosition().x + xMovement;
			newPos.y = mPlayer->getEntityPosition().y;
			mPlayer->setEntityPosition(newPos);
			mPlayer->getEntitySprite()->setSpritePosition(newPos);
		}
	}
}

void CGame::createBullet() {
	if (getCountEntitiesByType(CSprite::bullet) < MAX_BULLETS) {
		CEntity* newBullet = new CEntity();
		newBullet->setEntityType(CSprite::bullet);
		newBullet->setEntitySize(CSprite::midSize);

		vec2 bulletPos;
		bulletPos.x = mPlayer->getEntityPosition().x;
		bulletPos.y = mPlayer->getEntityPosition().y + 32;
		newBullet->setEntityPosition(bulletPos);

		CComponentInertialMovement*   componentEnemyInertialMovement = new CComponentInertialMovement (newBullet);
		CComponentRemovable*          componentEnemyRemovable        = new CComponentRemovable        (newBullet);
		CComponentRendereable*        componentEnemyRendereable      = new CComponentRendereable      (newBullet);

		CMessageRendereable msg;
		componentEnemyRendereable->receiveMessage(msg);

		newBullet->AddComponent (componentEnemyInertialMovement );
		newBullet->AddComponent (componentEnemyRemovable        );
		newBullet->AddComponent (componentEnemyRendereable      );

		mEntities.push_back(newBullet);
	}
}

void CGame::finishGame() {
	appManager->setWantedMode(MenuMode);
}

void CGame::checkCollisionBulletEnemy() {
	std::vector<CEntity*> enemiesToCreate;

	// Mark enemies and bullets when have collisions to remove them
	auto bulletIterator = mEntities.begin();
	for (int i = 0; bulletIterator < mEntities.end();) {
		CEntity *entityBullet = mEntities.at(i);

		if (entityBullet->getEntityType() == CSprite::bullet) {
			auto enemyIterator = mEntities.begin();
			for (int j = 0; enemyIterator < mEntities.end();) {
				CEntity *entityEnemy = mEntities.at(j);

				if (entityEnemy->getEntityType() == CSprite::enemy) {
					if (checkCollisionCircleCircle(entityBullet->getEntitySprite()->getSpritePosition(), static_cast<float>(entityBullet->getEntitySprite()->getSpriteSize()) / 2,
						entityEnemy->getEntitySprite()->getSpritePosition(), static_cast<float>(entityEnemy->getEntitySprite()->getSpriteSize()) / 2)) {

						CMessageSetRemovable msg;
						entityEnemy->manageMessage(&msg);

						CMessageSetRemovable msg2;
						entityBullet->manageMessage(&msg2);

						enemiesToCreate.push_back(entityEnemy);
					}
				}

				enemyIterator++;
				j++;
			}
		}

		bulletIterator++;
		i++;
	}

	// Create new enemies from old ones
	auto entityToCreateIterator = enemiesToCreate.begin();
	for (int i = 0; entityToCreateIterator < enemiesToCreate.end();) {
		CMessageGetOrientationInY msg3;
		(*entityToCreateIterator)->manageMessage(&msg3);

		CSprite::EOrientation oldEnemyOrientationInY = msg3.getOrientationInY();
		vec2 oldEnemyPosition = (*entityToCreateIterator)->getEntityPosition();

		if ((*entityToCreateIterator)->getEntitySprite()->getSpriteSize() != CSprite::smallSize) {
			for (int k = 0; k < 2; k++) {
				CEntity* newEnemy = new CEntity();
				newEnemy->setEntityType(CSprite::enemy);

				float posInX = 0.0f;
				CSprite::EOrientation newOrientationInX = CSprite::EOrientation::right;
				if (k > 0) {
					newOrientationInX = CSprite::EOrientation::left;
				}

				newEnemy->setEntityPosition(oldEnemyPosition);

				if ((*entityToCreateIterator)->getEntitySize() == CSprite::bigSize) {
					newEnemy->setEntitySize(CSprite::midSize);
				}
				else {
					newEnemy->setEntitySize(CSprite::smallSize);
				}

				CComponentElementOrientation* componentEnemyOrientation      = new CComponentElementOrientation (newEnemy);
				CComponentInertialMovement*   componentEnemyInertialMovement = new CComponentInertialMovement   (newEnemy);
				CComponentRemovable*          componentEnemyRemovable        = new CComponentRemovable          (newEnemy);
				CComponentRendereable*        componentRendereable           = new CComponentRendereable(newEnemy);

				CMessageRendereable msg4;
				componentRendereable->receiveMessage(msg4);

				componentEnemyOrientation->setOrientationInX(newOrientationInX);
				componentEnemyOrientation->setOrientationInY(oldEnemyOrientationInY);

				newEnemy->AddComponent (componentEnemyOrientation      );
				newEnemy->AddComponent (componentEnemyInertialMovement );
				newEnemy->AddComponent (componentEnemyRemovable        );
				newEnemy->AddComponent (componentRendereable           );

				mEntities.push_back(newEnemy);
			}
		}

		entityToCreateIterator++;
		i++;
	}

	// If no have enemies in map, exit the game to menu
	if (getCountEntitiesByType(CSprite::enemy) == 0) {
		appManager->setWantedMode(MenuMode);
	}
}

void CGame::checkCollisionEnemyCharacter() {
	auto enemyIterator = mEntities.begin();
	for (int i = 0; enemyIterator < mEntities.end(); i++) {
		CEntity* entity = mEntities.at(i);

		if (entity->getEntityType() == CSprite::enemy) {
			if (checkCollisionCircleCircle(entity->getEntitySprite()->getSpritePosition(), static_cast<float>(entity->getEntitySprite()->getSpriteSize()) / 2,
				mPlayer->getEntitySprite()->getSpritePosition(), static_cast<float>(mPlayer->getEntitySprite()->getSpriteSize()) / 2)) {

				// If enemy collide with character, exit the game to menu
				appManager->setWantedMode(MenuMode);
				break;
			}
		}
		enemyIterator++;
	}
}

void CGame::moveElements() {
	auto entityIterator = mEntities.begin();
	for (int i = 0; entityIterator < mEntities.end();) {
		CEntity *entity = mEntities.at(i);
		entity->update();
		entityIterator++;
		i++;
	}
}

void CGame::removeElements() {
	auto entityIterator = mEntities.begin();
	for (int i = 0; entityIterator < mEntities.end();) {
		CMessageGetRemovable msg;
		(*entityIterator)->manageMessage(&msg);

		if (msg.getRemovable()) {
			entityIterator = mEntities.erase(entityIterator);
		}
		else {
			entityIterator++;
			i++;
		}
	}

	graphicsEngine->removeSprites();
}

void CGame::usePauseMenuInput() {
	CModeAppGame* actualMode = (CModeAppGame*)appManager->getAppMode();

	actualMode->getActualMenu()->input();
}