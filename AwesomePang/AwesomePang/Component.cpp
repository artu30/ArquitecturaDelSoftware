#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "Sprite.h"
#include "Message.h"
#include "Component.h"
#include "Entity.h"
#include "GraphicsEngine.h"
#include "Global.h"

void CComponentRendereable::update() { }

void CComponentRemovable::update() { }

void CComponentElementOrientation::update() {
	// Change enemy orientation in X
	if (getOwner()->getEntityPosition().x < 0 + getOwner()->getEntitySprite()->getSpriteSize() / 2) {
		vec2 enemyPosition;
		enemyPosition.x = static_cast<float>(getOwner()->getEntitySprite()->getSpriteSize()) / 2;
		enemyPosition.y = getOwner()->getEntityPosition().y;
		getOwner()->setEntityPosition(enemyPosition);
		getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);

		setOrientationInX(CSprite::EOrientation::right);
	}
	else if (getOwner()->getEntityPosition().x > SCR_WIDTH - getOwner()->getEntitySprite()->getSpriteSize() / 2) {
		vec2 enemyPosition;
		enemyPosition.x = SCR_WIDTH - static_cast<float>(getOwner()->getEntitySprite()->getSpriteSize()) / 2;
		enemyPosition.y = getOwner()->getEntityPosition().y;
		getOwner()->setEntityPosition(enemyPosition);
		getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);

		setOrientationInX(CSprite::EOrientation::left);
	}

	// Change enemy orientation in Y
	if (getOwner()->getEntityPosition().y < 0 + getOwner()->getEntitySprite()->getSpriteSize() / 2) {
		vec2 enemyPosition;
		enemyPosition.y = static_cast<float>(getOwner()->getEntitySprite()->getSpriteSize()) / 2;
		enemyPosition.x = getOwner()->getEntityPosition().x;
		getOwner()->setEntityPosition(enemyPosition);
		getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);

		setOrientationInY(CSprite::EOrientation::down);
	}
	else if (getOwner()->getEntityPosition().y > SCR_HEIGHT - getOwner()->getEntitySprite()->getSpriteSize() / 2) {
		vec2 enemyPosition;
		enemyPosition.y = SCR_HEIGHT - static_cast<float>(getOwner()->getEntitySprite()->getSpriteSize()) / 2;
		enemyPosition.x = getOwner()->getEntityPosition().x;
		getOwner()->setEntityPosition(enemyPosition);
		getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);

		setOrientationInY(CSprite::EOrientation::up);
	}
}

void CComponentInertialMovement::update() {
	if (getOwner()->getEntityType() == CSprite::enemy) {
		// Enemy inertial movement
		vec2 enemyPosition;

		// Move enemy in X
		CMessageGetOrientationInX msg;
		getOwner()->manageMessage(&msg);

		if (msg.getOrientationInX() == CSprite::EOrientation::right) {
			switch (getOwner()->getEntitySprite()->getSpriteSize()) {
			case CSprite::bigSize:
				enemyPosition.y = getOwner()->getEntityPosition().y;
				enemyPosition.x = getOwner()->getEntityPosition().x + 1.5f;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::midSize:
				enemyPosition.y = getOwner()->getEntityPosition().y;
				enemyPosition.x = getOwner()->getEntityPosition().x + 2.0f;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::smallSize:
				enemyPosition.y = getOwner()->getEntityPosition().y;
				enemyPosition.x = getOwner()->getEntityPosition().x + 2.5f;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			}
		}
		else {
			switch (getOwner()->getEntitySprite()->getSpriteSize()) {
			case CSprite::bigSize:
				enemyPosition.y = getOwner()->getEntityPosition().y;
				enemyPosition.x = getOwner()->getEntityPosition().x - 1.5f;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::midSize:
				enemyPosition.y = getOwner()->getEntityPosition().y;
				enemyPosition.x = getOwner()->getEntityPosition().x - 2.0f;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::smallSize:
				enemyPosition.y = getOwner()->getEntityPosition().y;
				enemyPosition.x = getOwner()->getEntityPosition().x - 2.5f;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			}
		}

		// Move enemy in Y
		CMessageGetOrientationInY msg2;
		getOwner()->manageMessage(&msg2);

		if (msg2.getOrientationInY() == CSprite::EOrientation::down) {
			switch (getOwner()->getEntitySprite()->getSpriteSize()) {
			case CSprite::bigSize:
				enemyPosition.y = getOwner()->getEntityPosition().y + 1.5f;
				enemyPosition.x = getOwner()->getEntityPosition().x;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::midSize:
				enemyPosition.y = getOwner()->getEntityPosition().y + 2.0f;
				enemyPosition.x = getOwner()->getEntityPosition().x;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::smallSize:
				enemyPosition.y = getOwner()->getEntityPosition().y + 2.5f;
				enemyPosition.x = getOwner()->getEntityPosition().x;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			}
		}
		else {
			switch (getOwner()->getEntitySprite()->getSpriteSize()) {
			case CSprite::bigSize:
				enemyPosition.y = getOwner()->getEntityPosition().y - 1.5f;
				enemyPosition.x = getOwner()->getEntityPosition().x;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::midSize:
				enemyPosition.y = getOwner()->getEntityPosition().y - 2.0f;
				enemyPosition.x = getOwner()->getEntityPosition().x;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			case CSprite::smallSize:
				enemyPosition.y = getOwner()->getEntityPosition().y - 2.5f;
				enemyPosition.x = getOwner()->getEntityPosition().x;
				getOwner()->setEntityPosition(enemyPosition);
				getOwner()->getEntitySprite()->setSpritePosition(enemyPosition);
				break;
			}
		}
	}

	if (getOwner()->getEntityType() == CSprite::bullet) {
		// Bullet inertial movement
		if (getOwner()->getEntityPosition().y >= SCR_HEIGHT) {
			CMessageSetRemovable msg;
			getOwner()->manageMessage(&msg);
		}
		else {
			vec2 bulletPosition;
			bulletPosition.x = getOwner()->getEntityPosition().x;
			bulletPosition.y = getOwner()->getEntityPosition().y + 4;
			getOwner()->setEntityPosition(bulletPosition);
			getOwner()->getEntitySprite()->setSpritePosition(bulletPosition);
		}
	}
}

void CComponentRendereable::receiveMessage(CMessage &msg) {
	switch (msg.getType()) {
		case CMessage::ERendereable:
			CSprite * sprite = new CSprite();
			sprite->setRemovableSprite(false);
			sprite->setSpritePosition(getOwner()->getEntityPosition());
			sprite->setSpriteSize(getOwner()->getEntitySize());
			sprite->setSpriteType(getOwner()->getEntityType());

			graphicsEngine->addSprite(sprite);

			getOwner()->setEntitySprite(sprite);

			break;
	}
}

void CComponentRemovable::receiveMessage(CMessage &msg) {
	switch (msg.getType()) {
		case CMessage::ESetRemovable:
			setRemovable(true);
			getOwner()->getEntitySprite()->setRemovableSprite(true);
			break;

		case CMessage::EGetRemovable:
			static_cast<CMessageGetRemovable&>(msg).setRemovable(getRemovable());
			break;
	}
}

void CComponentElementOrientation::receiveMessage(CMessage &msg) {
	switch (msg.getType()) {
		case CMessage::EGetOrientationInX:
			static_cast<CMessageGetOrientationInX&>(msg).setOrientationInX(getOrientationInX());
			break;

		case CMessage::EGetOrientationInY:
			static_cast<CMessageGetOrientationInY&>(msg).setOrientationInY(getOrientationInY());
			break;

		case CMessage::ESetOrientationInX:
			setOrientationInX(static_cast<CMessageSetOrientationInX&>(msg).getOrientationInX());
			break;

		case CMessage::ESetOrientationInY:
			setOrientationInY(static_cast<CMessageSetOrientationInY&>(msg).getOrientationInY());
			break;
	}
}