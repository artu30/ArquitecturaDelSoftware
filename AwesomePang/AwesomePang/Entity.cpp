#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include <vector>
#include "Sprite.h"
#include "Message.h"
#include "Component.h"
#include "Entity.h"

CEntity::~CEntity() {
	for (auto iterator = mComponents.begin(); iterator != mComponents.end(); ++iterator) {
		delete *iterator;
	}
	
	mComponents.clear();
}

vec2 CEntity::getEntityPosition () const { return mEntityPosition; }

void CEntity::setEntityPosition (vec2 position)      { mEntityPosition = position; }

CSprite*      CEntity::getEntitySprite() const { return mEntitySprite; }
CSprite::Type CEntity::getEntityType  () const { return mEntityType; }
CSprite::Size CEntity::getEntitySize  () const { return mEntitySize; }

void  CEntity::setEntitySprite(CSprite* sprite)    { mEntitySprite = sprite; }
void  CEntity::setEntityType  (CSprite::Type type) { mEntityType = type; }
void  CEntity::setEntitySize  (CSprite::Size size) { mEntitySize = size; }

// Add component
void CEntity::AddComponent(CComponent* component) {
	mComponents.push_back(component);
}

// Entity update
void CEntity::update() { 
	for (auto iterator = mComponents.begin(); iterator != mComponents.end(); iterator++) {
		(*iterator)->update();
	}
}

// Manage messages between components
void CEntity::manageMessage(CMessage* pMsg) {
	for (auto iterator = mComponents.begin(); iterator != mComponents.end(); iterator++) {
		(*iterator)->receiveMessage(*pMsg);
	}
}