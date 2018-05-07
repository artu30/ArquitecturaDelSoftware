class CModeAppGame;

class CPauseMenu : public CMenu {
public:
	CPauseMenu(CModeAppGame* owner);

	enum EOption {
		restart,
		exit
	};

	void input();
	void run();
	void render();

private:
	CModeAppGame *               mOwner;
	EOption                      mOptionSelected;
	std::vector<CItemSelectable> mMenuItems;
};