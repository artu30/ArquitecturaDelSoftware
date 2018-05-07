#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "Sprite.h"
#include "ItemSelectable.h"
#include "Menu.h"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "AppManager.h"
#include "Global.h"

#define ENTER_KEY 13
#define ESC_KEY   27

COptionsMenu::COptionsMenu(CModeAppMenu* owner) {
	mOwner = owner;

	mOptionSelected = sound;

	CItemSelectable item1("sound");
	CItemSelectable item2("effects");
	CItemSelectable item3("language");
	CItemSelectable item4("returnMenu");

	item1.setFunction(&CAppManager::isSoundEnabled);
	item2.setFunction(&CAppManager::isEffectsEnabled);
	item3.setFunction(&CAppManager::isInEnglishLanguage);

	vec2 position1;
	position1.x = SCR_WIDTH / 4;
	position1.y = SCR_HEIGHT / 1.2f - 100;
	item1.setPosition(position1);

	vec2 position2;
	position2.x = SCR_WIDTH / 4;
	position2.y = SCR_HEIGHT / 1.2f - 200;
	item2.setPosition(position2);

	vec2 position3;
	position3.x = SCR_WIDTH / 4;
	position3.y = SCR_HEIGHT / 1.2f - 300;
	item3.setPosition(position3);

	vec2 position4;
	position4.x = SCR_WIDTH / 4;
	position4.y = SCR_HEIGHT / 1.2f - 380;
	item4.setPosition(position4);

	mMenuItems.push_back(item1);
	mMenuItems.push_back(item2);
	mMenuItems.push_back(item3);
	mMenuItems.push_back(item4);
}

void COptionsMenu::input() {
	if (SYS_KeyPressed(SYS_KEY_UP) && !appManager->getUpKeyPressed()) {
		if (mOptionSelected != sound) {
			if (mOptionSelected == effects) {
				mOptionSelected = sound;
			}
			else {
				mOptionSelected = effects;
			}
		}
	}

	if (SYS_KeyPressed(SYS_KEY_DOWN) && !appManager->getDownKeyPressed()) {
		if (mOptionSelected != language) {
			if (mOptionSelected == effects) {
				mOptionSelected = language;
			}
			else {
				mOptionSelected = effects;
			}
		}
	}

	if (SYS_KeyPressed(ENTER_KEY) && !appManager->getEnterKeyPressed()) {
		if (mOptionSelected == sound) {
			if (appManager->getSound()) {
				appManager->setSound(false);
			}
			else {
				appManager->setSound(true);
			}
		}
		if (mOptionSelected == effects) {
			if (appManager->getEffects()) {
				appManager->setEffects(false);
			}
			else {
				appManager->setEffects(true);
			}
		}
		if (mOptionSelected == language) {
			if (appManager->getLanguage() == CAppManager::ELanguage::Spanish) {
				appManager->setLanguaje(CAppManager::ELanguage::English);
			}
			else {
				appManager->setLanguaje(CAppManager::ELanguage::Spanish);
			}
		}
	}

	if (SYS_KeyPressed(ESC_KEY)) {
		CMainMenu* mainMenu = new CMainMenu(mOwner);
		mOwner->setActualMenu(mainMenu);
	}

	// Controll up key press
	if (SYS_KeyPressed(SYS_KEY_UP)) {
		appManager->setUpKeyPressed(true);
	}
	else {
		appManager->setUpKeyPressed(false);
	}

	// Controll down key press
	if (SYS_KeyPressed(SYS_KEY_DOWN)) {
		appManager->setDownKeyPressed(true);
	}
	else {
		appManager->setDownKeyPressed(false);
	}

	// Controll enter key press
	if (SYS_KeyPressed(ENTER_KEY)) {
		appManager->setEnterKeyPressed(true);
	}
	else {
		appManager->setEnterKeyPressed(false);
	}
}

void COptionsMenu::run() {

}

void COptionsMenu::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	FONT_DrawString(vmake(SCR_WIDTH / 6, SCR_HEIGHT / 1.2f), "AWESOMEPANG!!!");

	for (auto it = mMenuItems.begin(); it != mMenuItems.end(); ++it) {
		it->render(appManager->getTextInMap(it->getReference()).c_str());
	}

	switch (mOptionSelected) {
		case sound:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 250, SCR_HEIGHT / 1.2f - 100), " <--");
			break;
		case effects:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 250, SCR_HEIGHT / 1.2f - 200), " <--");
			break;
		case language:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 300, SCR_HEIGHT / 1.2f - 300), " <--");
			break;
	}

	SYS_Show();
}