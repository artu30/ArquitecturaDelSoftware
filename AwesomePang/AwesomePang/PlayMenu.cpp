#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "Sprite.h"
#include "ItemSelectable.h"
#include "Menu.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "AppManager.h"
#include "Global.h"

#define ESC_KEY     27
#define ENTER_KEY 13

CPlayMenu::CPlayMenu(CModeAppMenu* owner) {
	mOwner = owner;

	mOptionSelected = easy;

	CItemSelectable item1("easyGame");
	CItemSelectable item2("medGame");
	CItemSelectable item3("hardGame");
	CItemSelectable item4("returnMenu");

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

void CPlayMenu::input() {
	if (SYS_KeyPressed(SYS_KEY_UP) && !appManager->getUpKeyPressed()) {
		if (mOptionSelected != easy) {
			if (mOptionSelected == medium) {
				mOptionSelected = easy;
			}
			else {
				mOptionSelected = medium;
			}
		}
	}

	if (SYS_KeyPressed(SYS_KEY_DOWN) && !appManager->getDownKeyPressed()) {
		if (mOptionSelected != hard) {
			if (mOptionSelected == medium) {
				mOptionSelected = hard;
			}
			else {
				mOptionSelected = medium;
			}
		}
	}

	if (SYS_KeyPressed(ENTER_KEY) && !appManager->getEnterKeyPressed()) {
		if (mOptionSelected == easy){
			appManager->setGameLevel(CAppManager::easyLevel);
		}
		if (mOptionSelected == medium) {
			appManager->setGameLevel(CAppManager::midLevel);
		}
		if (mOptionSelected == hard) {
			appManager->setGameLevel(CAppManager::hardLevel);
		}

		appManager->setWantedMode(GameMode);
	}

	if (SYS_KeyPressed(ESC_KEY))
	{
		CMainMenu* mainMenu = new CMainMenu(mOwner);
		mOwner->setActualMenu(mainMenu);
	}

	// Controll up key press
	if (SYS_KeyPressed(SYS_KEY_UP))
	{
		appManager->setUpKeyPressed(true);
	}
	else
	{
		appManager->setUpKeyPressed(false);
	}

	// Controll down key press
	if (SYS_KeyPressed(SYS_KEY_DOWN))
	{
		appManager->setDownKeyPressed(true);
	}
	else
	{
		appManager->setDownKeyPressed(false);
	}

	// Controll enter key press
	if (SYS_KeyPressed(ENTER_KEY))
	{
		appManager->setEnterKeyPressed(true);
	}
	else
	{
		appManager->setEnterKeyPressed(false);
	}
}

void CPlayMenu::run() {

}

void CPlayMenu::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	FONT_DrawString(vmake(SCR_WIDTH / 6, SCR_HEIGHT / 1.2f), "AWESOMEPANG!!!");

	for (auto it = mMenuItems.begin(); it != mMenuItems.end(); ++it) {
		it->render(appManager->getTextInMap(it->getReference()).c_str());
	}

	switch (mOptionSelected) {
		case easy:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 200, SCR_HEIGHT / 1.2f - 100), " <--");
			break;
		case medium:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 200, SCR_HEIGHT / 1.2f - 200), " <--");
			break;
		case hard:
			FONT_DrawString(vmake(SCR_WIDTH / 4 + 200, SCR_HEIGHT / 1.2f - 300), " <--");
			break;
	}

	if (appManager->getLevelsError()) {
		FONT_DrawString(vmake(SCR_WIDTH / 8, SCR_HEIGHT / 1.2f - 400), "ERROR IN LEVELS FILE!");
	}

	SYS_Show();
}