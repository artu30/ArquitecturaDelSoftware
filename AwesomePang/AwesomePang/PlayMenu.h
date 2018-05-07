class CModeAppMenu;

class CPlayMenu : public CMenu {
public:
	CPlayMenu(CModeAppMenu* owner);

	enum EOption {
		easy,
		medium,
		hard
	};

	void input ();
	void run   ();
	void render();

private:
	CModeAppMenu *               mOwner;
	std::vector<CItemSelectable> mMenuItems;
	EOption                      mOptionSelected;
};