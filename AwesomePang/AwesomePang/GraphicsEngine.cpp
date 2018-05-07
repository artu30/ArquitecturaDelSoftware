#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "Sprite.h"
#include "GraphicsEngine.h"

CGraphicsEngine::~CGraphicsEngine() {
	for (auto textureIterator = mGameTextures.begin(); textureIterator != mGameTextures.end(); textureIterator++) {
		CORE_UnloadPNG(textureIterator->mTextureId);
	}

	for (auto iterator = mSprites.begin(); iterator != mSprites.end(); ++iterator) {
		delete *iterator;
	}
	mSprites.clear();
}

void CGraphicsEngine::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Paint all sprites
	for (auto iterator = mSprites.begin(); iterator != mSprites.end(); iterator++) {
		GLuint textureID = getTexture((*iterator)->getSpriteType());

		CORE_RenderCenteredSprite((*iterator)->getSpritePosition(), vmake(static_cast<float>((*iterator)->getSpriteSize()), static_cast<float>((*iterator)->getSpriteSize())), textureID);
	}

	SYS_Show();
}

// Get texture by type
GLuint CGraphicsEngine::getTexture(CSprite::Type type) const {
	for (auto textureIterator = mGameTextures.begin(); textureIterator < mGameTextures.end(); textureIterator++) {
		if (textureIterator->mType == type) {
			return textureIterator->mTextureId;
		}
	}

	return 0;
}

// Adds a texture to game
void CGraphicsEngine::addTexture(Texture texture) {
	mGameTextures.push_back(texture);
}

// Remove texture from game
bool CGraphicsEngine::removeTexture(CSprite::Type type) {
	bool textureFinded = false;

	for (auto textureIterator = mGameTextures.begin(); textureIterator < mGameTextures.end(); textureIterator++) {
		if (textureIterator->mType == type) {
			textureFinded = true;
			mGameTextures.erase(textureIterator);
			break;
		}
	}

	if (!textureFinded) {
		return false;
	}

	return true;
}

// Adds a Sprite
void CGraphicsEngine::addSprite(CSprite* sprite) {
	mSprites.push_back(sprite);
}

void CGraphicsEngine::removeSprites() {
	auto iterator = mSprites.begin();
	for (int i = 0; iterator < mSprites.end();) {
		if ((*iterator)->getRemovableSprite()) {
			iterator = mSprites.erase(iterator);
		}
		else {
			iterator++;
			i++;
		}
	}
}

int CGraphicsEngine::getNumEnemies() const {
	return mNumEnemies;
}

void CGraphicsEngine::setNumEnemies(int enemies) {
	mNumEnemies = enemies;
}