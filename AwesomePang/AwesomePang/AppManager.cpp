#include "stdafx.h"
#include "sys.h"
#include "core.h"
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

using namespace rapidjson;
using namespace std;

CAppManager::AppOptions CAppManager::mAppOptions;

CAppManager::CAppManager() {
	mActiveModeApp = new CModeAppMenu();

	mWantedMode = NullMode;

	mGamelevel = onMenu;

	mLevelsError = false;

	mAppOptions.mEffects = false;
	mAppOptions.mSound = false;
	mAppOptions.mLanguage = English;

	ifstream ifs("data/language.json");
	IStreamWrapper isw(ifs);
	Document d;
	d.ParseStream(isw);

	if (!d.HasParseError()) {
		if (d.IsObject()) {
			// Start
			if (d.HasMember("start")) {
				if (d["start"].HasMember("english")) {
					if (d["start"]["english"].IsString()) {
						std::string startEnglish = d["start"]["english"].GetString();

						mEnglishMap["start"] = startEnglish;
					}
				}
				if (d["start"].HasMember("spanish")) {
					if (d["start"]["spanish"].IsString()) {
						std::string startSpanish = d["start"]["spanish"].GetString();

						mSpanishMap["start"] = startSpanish;
					}
				}
			}

			// Options
			if (d.HasMember("options")) {
				if (d["options"].HasMember("english")) {
					if (d["options"]["english"].IsString()) {
						std::string startEnglish = d["options"]["english"].GetString();

						mEnglishMap["options"] = startEnglish;
					}
				}
				if (d["options"].HasMember("spanish")) {
					if (d["options"]["spanish"].IsString()) {
						std::string startSpanish = d["options"]["spanish"].GetString();

						mSpanishMap["options"] = startSpanish;
					}
				}
			}

			// Exit
			if (d.HasMember("exit")) {
				if (d["exit"].HasMember("english")) {
					if (d["exit"]["english"].IsString()) {
						std::string startEnglish = d["exit"]["english"].GetString();

						mEnglishMap["exit"] = startEnglish;
					}
				}
				if (d["exit"].HasMember("spanish")) {
					if (d["exit"]["spanish"].IsString()) {
						std::string startSpanish = d["exit"]["spanish"].GetString();

						mSpanishMap["exit"] = startSpanish;
					}
				}
			}

			// Sound
			if (d.HasMember("sound")) {
				if (d["sound"].HasMember("english")) {
					if (d["sound"]["english"].IsString()) {
						std::string startEnglish = d["sound"]["english"].GetString();

						mEnglishMap["sound"] = startEnglish;
					}
				}
				if (d["sound"].HasMember("spanish")) {
					if (d["sound"]["spanish"].IsString()) {
						std::string startSpanish = d["sound"]["spanish"].GetString();

						mSpanishMap["sound"] = startSpanish;
					}
				}
			}

			// Effects
			if (d.HasMember("effects")) {
				if (d["effects"].HasMember("english")) {
					if (d["effects"]["english"].IsString()) {
						std::string startEnglish = d["effects"]["english"].GetString();

						mEnglishMap["effects"] = startEnglish;
					}
				}
				if (d["effects"].HasMember("spanish")) {
					if (d["effects"]["spanish"].IsString()) {
						std::string startSpanish = d["effects"]["spanish"].GetString();

						mSpanishMap["effects"] = startSpanish;
					}
				}
			}

			// Language
			if (d.HasMember("language")) {
				if (d["language"].HasMember("english")) {
					if (d["language"]["english"].IsString()) {
						std::string startEnglish = d["language"]["english"].GetString();

						mEnglishMap["language"] = startEnglish;
					}
				}
				if (d["language"].HasMember("spanish")) {
					if (d["language"]["spanish"].IsString()) {
						std::string startSpanish = d["language"]["spanish"].GetString();

						mSpanishMap["language"] = startSpanish;
					}
				}
			}

			// Paused
			if (d.HasMember("paused")) {
				if (d["paused"].HasMember("english")) {
					if (d["paused"]["english"].IsString()) {
						std::string startEnglish = d["paused"]["english"].GetString();

						mEnglishMap["paused"] = startEnglish;
					}
				}
				if (d["paused"].HasMember("spanish")) {
					if (d["paused"]["spanish"].IsString()) {
						std::string startSpanish = d["paused"]["spanish"].GetString();

						mSpanishMap["paused"] = startSpanish;
					}
				}
			}

			// Return to game
			if (d.HasMember("returnToGame")) {
				if (d["returnToGame"].HasMember("english")) {
					if (d["returnToGame"]["english"].IsString()) {
						std::string startEnglish = d["returnToGame"]["english"].GetString();

						mEnglishMap["returnToGame"] = startEnglish;
					}
				}
				if (d["returnToGame"].HasMember("spanish")) {
					if (d["returnToGame"]["spanish"].IsString()) {
						std::string startSpanish = d["returnToGame"]["spanish"].GetString();

						mSpanishMap["returnToGame"] = startSpanish;
					}
				}
			}

			// Choose game
			if (d.HasMember("chooseGame")) {
				if (d["chooseGame"].HasMember("english")) {
					if (d["chooseGame"]["english"].IsString()) {
						std::string startEnglish = d["chooseGame"]["english"].GetString();

						mEnglishMap["chooseGame"] = startEnglish;
					}
				}
				if (d["chooseGame"].HasMember("spanish")) {
					if (d["chooseGame"]["spanish"].IsString()) {
						std::string startSpanish = d["chooseGame"]["spanish"].GetString();

						mSpanishMap["chooseGame"] = startSpanish;
					}
				}
			}

			// Easy game
			if (d.HasMember("easyGame")) {
				if (d["easyGame"].HasMember("english")) {
					if (d["easyGame"]["english"].IsString()) {
						std::string startEnglish = d["easyGame"]["english"].GetString();

						mEnglishMap["easyGame"] = startEnglish;
					}
				}
				if (d["easyGame"].HasMember("spanish")) {
					if (d["easyGame"]["spanish"].IsString()) {
						std::string startSpanish = d["easyGame"]["spanish"].GetString();

						mSpanishMap["easyGame"] = startSpanish;
					}
				}
			}

			// Medium game
			if (d.HasMember("medGame")) {
				if (d["medGame"].HasMember("english")) {
					if (d["medGame"]["english"].IsString()) {
						std::string startEnglish = d["medGame"]["english"].GetString();

						mEnglishMap["medGame"] = startEnglish;
					}
				}
				if (d["medGame"].HasMember("spanish")) {
					if (d["medGame"]["spanish"].IsString()) {
						std::string startSpanish = d["medGame"]["spanish"].GetString();

						mSpanishMap["medGame"] = startSpanish;
					}
				}
			}

			// Hard game
			if (d.HasMember("hardGame")) {
				if (d["hardGame"].HasMember("english")) {
					if (d["hardGame"]["english"].IsString()) {
						std::string startEnglish = d["hardGame"]["english"].GetString();

						mEnglishMap["hardGame"] = startEnglish;
					}
				}
				if (d["hardGame"].HasMember("spanish")) {
					if (d["hardGame"]["spanish"].IsString()) {
						std::string startSpanish = d["hardGame"]["spanish"].GetString();

						mSpanishMap["hardGame"] = startSpanish;
					}
				}
			}

			// Return menu
			if (d.HasMember("returnMenu")) {
				if (d["returnMenu"].HasMember("english")) {
					if (d["returnMenu"]["english"].IsString()) {
						std::string startEnglish = d["returnMenu"]["english"].GetString();

						mEnglishMap["returnMenu"] = startEnglish;
					}
				}
				if (d["returnMenu"].HasMember("spanish")) {
					if (d["returnMenu"]["spanish"].IsString()) {
						std::string startSpanish = d["returnMenu"]["spanish"].GetString();

						mSpanishMap["returnMenu"] = startSpanish;
					}
				}
			}

			// Error message
			if (d.HasMember("errorInLevelsFile")) {
				if (d["errorInLevelsFile"].HasMember("english")) {
					if (d["errorInLevelsFile"]["english"].IsString()) {
						std::string startEnglish = d["errorInLevelsFile"]["english"].GetString();

						mEnglishMap["errorInLevelsFile"] = startEnglish;
					}
				}
				if (d["errorInLevelsFile"].HasMember("spanish")) {
					if (d["errorInLevelsFile"]["spanish"].IsString()) {
						std::string startSpanish = d["errorInLevelsFile"]["spanish"].GetString();

						mSpanishMap["errorInLevelsFile"] = startSpanish;
					}
				}
			}

			// Is paused message
			if (d.HasMember("pausedText"))
			{
				if (d["pausedText"].HasMember("english"))
				{
					if (d["pausedText"]["english"].IsString())
					{
						std::string startEnglish = d["pausedText"]["english"].GetString();

						mEnglishMap["pausedText"] = startEnglish;
					}
				}
				if (d["pausedText"].HasMember("spanish"))
				{
					if (d["pausedText"]["spanish"].IsString())
					{
						std::string startSpanish = d["pausedText"]["spanish"].GetString();

						mSpanishMap["pausedText"] = startSpanish;
					}
				}
			}
		}
	}

	mSelectedMap = &mEnglishMap;
}

CAppManager::~CAppManager() {
	delete mActiveModeApp;
	mActiveModeApp = nullptr;

	delete mSelectedMap;
	mSelectedMap = nullptr;
}

CModeApp* CAppManager::getAppMode() const{
	return mActiveModeApp;
}

std::string CAppManager::getTextInMap(std::string key) const {
	std::string valueString = mSelectedMap->at(key);

	return valueString;
}

void CAppManager::processInput() {
	mActiveModeApp->input();
}
void CAppManager::run() {
	mActiveModeApp->run();
}
void CAppManager::render() {
	mActiveModeApp->render();
}

void CAppManager::setWantedMode(Mode wantedMode) {
	mWantedMode = wantedMode;
}

void CAppManager::setGameLevel(CAppManager::gameLevel level) {
	mGamelevel = level;
}

CAppManager::gameLevel CAppManager::getGameLevel() const {
	return mGamelevel;
}

void CAppManager::setLevelsError(bool haveError) {
	mLevelsError = haveError;
}

bool CAppManager::getLevelsError() const {
	return mLevelsError;
}

void CAppManager::setSound(bool sound) {
	mAppOptions.mSound = sound;
}

void CAppManager::setEffects(bool effects) {
	mAppOptions.mEffects = effects;
}

void CAppManager::setLanguaje(ELanguage language) {
	mAppOptions.mLanguage = language;

	if (language == English) {
		mSelectedMap = &mEnglishMap;
	}
	else {
		mSelectedMap = &mSpanishMap;
	}
}

std::string CAppManager::isSoundEnabled() {
	if (mAppOptions.mSound) {
		return " -- ON";
	}
	else {
		return " -- OFF";
	}
}

std::string CAppManager::isEffectsEnabled() {
	if (mAppOptions.mEffects) {
		return " -- ON";
	}
	else {
		return " -- OFF";
	}
}

std::string CAppManager::isInEnglishLanguage() {
	if (mAppOptions.mLanguage == English) {
		return " -- ENGLISH";
	}
	else {
		return " -- SPANISH";
	}
}

bool CAppManager::getSound() const {
	return mAppOptions.mSound;
}

bool CAppManager::getEffects() const {
	return mAppOptions.mEffects;
}

CAppManager::ELanguage CAppManager::getLanguage() const {
	return mAppOptions.mLanguage;
}

CAppManager::AppOptions CAppManager::getAppOptions() {
	return mAppOptions;
}

void CAppManager::manageMode() {
	Mode actualMode = mActiveModeApp->getId();
	if (actualMode == NullMode || (actualMode != mWantedMode && mWantedMode != NullMode)) {
		if ((mActiveModeApp == nullptr && mWantedMode != NullMode)
			|| (mActiveModeApp != nullptr && mActiveModeApp->getId() != mWantedMode)) {

			// Got to change mode, first disable the previous one
			if (mActiveModeApp) {
				mActiveModeApp->NotifyDeactivation();
				delete mActiveModeApp;
				mActiveModeApp = nullptr;
			}

			// Now, create & activate the new one
			switch (mWantedMode) {
			case NullMode:
			case MenuMode:
				mActiveModeApp = new CModeAppMenu();
				mActiveModeApp->NotifyActivation();
				break;
			case GameMode:
				mActiveModeApp = new CModeAppGame();
				mActiveModeApp->NotifyActivation();
				break;
			}
		}
	}
}

void CAppManager::setDownKeyPressed(bool pressed) {
	mDownKeyPressed = pressed;
}

void CAppManager::setUpKeyPressed(bool pressed) {
	mUpKeyPressed = pressed;
}

void CAppManager::setEnterKeyPressed(bool pressed) {
	mEnterKeyPressed = pressed;
}

bool CAppManager::getDownKeyPressed() const {
	return mDownKeyPressed;
}

bool CAppManager::getUpKeyPressed() const {
	return mUpKeyPressed;
}

bool CAppManager::getEnterKeyPressed() const {
	return mEnterKeyPressed;
}