#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "ItemSelectable.h"


CItemSelectable::CItemSelectable(std::string reference) {
	mReference = reference;
	mFunction = nullptr;
}

void CItemSelectable::setReference(std::string id) {
	mReference = id;
}

std::string CItemSelectable::getReference() const {
	return mReference;
}

void CItemSelectable::setPosition(vec2 position) {
	mPosition = position;
}

vec2 CItemSelectable::getPosition() const {
	return mPosition;
}

void CItemSelectable::setFunction(std::string(*func)()) {
	mFunction = func;
}

void CItemSelectable::render(std::string text) {
	FONT_DrawString(vmake(getPosition().x, getPosition().y), text.c_str());
	if (mFunction)
	{
		FONT_DrawString(vmake(getPosition().x + 150, getPosition().y), mFunction().c_str());
	}
}
