#include "ModeApp.h"
#include "ModeAppGame.h"
#include "ModeAppMenu.h"

class CAppManager {
public:
	enum gameLevel {
		onMenu,
		easyLevel,
		midLevel,
		hardLevel
	};

	enum ELanguage {
		Spanish,
		English
	};

	struct AppOptions {
		bool      mSound;
		bool      mEffects;
		ELanguage mLanguage;
	};

	CAppManager ();
	~CAppManager();

	void processInput();
	void run         ();
	void render      ();

	void manageMode();

	void setWantedMode(Mode wantedMode);

	CModeApp* getAppMode() const;

	void      setGameLevel(gameLevel level);
	gameLevel getGameLevel() const;

	void setLevelsError(bool haveError);
	bool getLevelsError() const;

	// Menu options
	AppOptions getAppOptions();

	void setSound   (bool sound);
	void setEffects (bool effects);
	void setLanguaje(ELanguage language);

	bool      getSound   () const;
	bool      getEffects () const;
	ELanguage getLanguage() const;

	static std::string isSoundEnabled     ();
	static std::string isEffectsEnabled   ();
	static std::string isInEnglishLanguage();

	// Get text in the appropriate language
	std::string getTextInMap(std::string key) const;

	// Keys press controller
	void setDownKeyPressed (bool pressed);
	void setUpKeyPressed   (bool pressed);
	void setEnterKeyPressed(bool pressed);

	bool getDownKeyPressed () const;
	bool getUpKeyPressed   () const;
	bool getEnterKeyPressed() const;

private:
	CModeApp*                           mActiveModeApp;
	Mode                                mWantedMode;
	gameLevel                           mGamelevel;
	bool                                mLevelsError;
	static AppOptions                   mAppOptions;
	std::map<std::string, std::string>* mSelectedMap;
	std::map<std::string, std::string>  mEnglishMap;
	std::map<std::string, std::string>  mSpanishMap;
	bool                                mDownKeyPressed;
	bool                                mUpKeyPressed;
	bool                                mEnterKeyPressed;
};