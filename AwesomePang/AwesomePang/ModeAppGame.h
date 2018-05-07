class CModeAppGame : public CModeApp {
public:
	CModeAppGame ();
	~CModeAppGame();

	void input ();
	void run   ();
	void render();

	void   setActualMenu(CMenu* menu);
	CMenu* getActualMenu() const;

	void NotifyActivation  ();
	void NotifyDeactivation();

	Mode getId() const;

private:
	CMenu * mActualMenu;
};