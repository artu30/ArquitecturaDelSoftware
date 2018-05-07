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
#include "Global.h"

CModeAppMenu::CModeAppMenu() {
	mActualMenu = new CMainMenu(this);
}

CModeAppMenu::~CModeAppMenu() {
	delete mActualMenu;
	mActualMenu = nullptr;
}

void CModeAppMenu::setActualMenu(CMenu* menu) {
	if (menu) {
		delete mActualMenu;
		mActualMenu = nullptr;

		mActualMenu = menu;
	}
}

CMenu* CModeAppMenu::getActualMenu() const {
	return mActualMenu;
}

void CModeAppMenu::input() {
	mActualMenu->input();
}

void CModeAppMenu::run() { }

void CModeAppMenu::render() {
	mActualMenu->render();
}

void CModeAppMenu::NotifyActivation   () { }

void CModeAppMenu::NotifyDeactivation () { }

Mode CModeAppMenu::getId() const {
	return MenuMode;
}