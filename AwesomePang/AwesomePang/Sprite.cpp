#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "Sprite.h"

CSprite::Type CSprite::getSpriteType      () const { return mSpriteType;     }
vec2          CSprite::getSpritePosition  () const { return mSpritePosition; }
CSprite::Size CSprite::getSpriteSize      () const { return mSpriteSize;     }
bool          CSprite::getRemovableSprite () const { return mSpriteToDelete; }

void CSprite::setSpriteType      (CSprite::Type type) { mSpriteType = type;         }
void CSprite::setSpritePosition  (vec2 position)      { mSpritePosition = position; }
void CSprite::setSpriteSize      (CSprite::Size size) { mSpriteSize = size;         }
void CSprite::setRemovableSprite (bool toRemove)      { mSpriteToDelete = toRemove; }