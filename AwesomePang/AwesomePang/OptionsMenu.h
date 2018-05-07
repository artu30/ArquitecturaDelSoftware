class CModeAppMenu;

class COptionsMenu : public CMenu {
public:
	COptionsMenu(CModeAppMenu* owner);

	enum EOption {
		sound,
		effects,
		language
	};

	void input ();
	void run   ();
	void render();

private:
	CModeAppMenu *               mOwner;
	EOption                      mOptionSelected;
	std::vector<CItemSelectable> mMenuItems;
};