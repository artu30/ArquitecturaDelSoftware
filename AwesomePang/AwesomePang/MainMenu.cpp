#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "Sprite.h"
#include "ItemSelectable.h"
#include "Menu.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "OptionsMenu.h"
#include "AppManager.h"
#include "Global.h"

#define ENTER_KEY 13

CMainMenu::CMainMenu(CModeAppMenu* owner){
	mOwner = owner;

	mOptionSelected = start;

	CItemSelectable item1("start");
	CItemSelectable item2("options");
	CItemSelectable item3("exit");

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

	mMenuItems.push_back(item1);
	mMenuItems.push_back(item2);
	mMenuItems.push_back(item3);
}

void CMainMenu::input() {
	if (SYS_KeyPressed(SYS_KEY_UP) && !appManager->getUpKeyPressed()) {
		if (mOptionSelected != start) {
			if (mOptionSelected == options) {
				mOptionSelected = start;
			}
			else {
				mOptionSelected = options;
			}
		}
	}

	if (SYS_KeyPressed(SYS_KEY_DOWN) && !appManager->getDownKeyPressed()) {
		if (mOptionSelected != exitGame) {
			if (mOptionSelected == options) {
				mOptionSelected = exitGame;
			}
			else {
				mOptionSelected = options;
			}
		}
	}

	if (SYS_KeyPressed(ENTER_KEY) && !appManager->getEnterKeyPressed()) {
		if (mOptionSelected == start) {
			CPlayMenu* playMenu = new CPlayMenu(mOwner);
			mOwner->setActualMenu(playMenu);
		}
		if (mOptionSelected == options) {
			COptionsMenu* optionsMenu = new COptionsMenu(mOwner);
			mOwner->setActualMenu(optionsMenu);
		}
		if (mOptionSelected == exitGame) {
			exit(0);
		}
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

void CMainMenu::run() {

}

void CMainMenu::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	std::string arrow = "-->";

	FONT_DrawString(vmake(SCR_WIDTH / 6, SCR_HEIGHT / 1.2f), "AWESOMEPANG!!!");

	for (auto it = mMenuItems.begin(); it != mMenuItems.end(); ++it) {
		it->render(appManager->getTextInMap(it->getReference()).c_str());
	}

	switch (mOptionSelected) {
		case start:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 100, SCR_HEIGHT / 1.2f - 100), " <--");
			break;
		case options:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 100, SCR_HEIGHT / 1.2f - 200), " <--");
			break;
		case exitGame:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 100, SCR_HEIGHT / 1.2f - 300), " <--");
			break;
	}

	SYS_Show();
}