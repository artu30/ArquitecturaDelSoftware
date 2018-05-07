class CModeAppMenu : public CModeApp {
public:
	CModeAppMenu ();
	~CModeAppMenu();

	void input ();
	void run   ();
	void render();

	void NotifyActivation  ();
	void NotifyDeactivation();

	void   setActualMenu(CMenu* menu);
	CMenu* getActualMenu() const;

	Mode getId() const;

private:
	CMenu* mActualMenu;
};