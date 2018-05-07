class CModeAppMenu;

class CMainMenu : public CMenu {
public:
	CMainMenu(CModeAppMenu* owner);

	enum EOption {
		start,
		options,
		exitGame
	};

	void input ();
	void run   ();
	void render();

private:
	EOption                      mOptionSelected;
	CModeAppMenu*                mOwner;
	std::vector<CItemSelectable> mMenuItems;
};