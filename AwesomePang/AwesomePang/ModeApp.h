enum Mode {
	NullMode,
	MenuMode,
	GameMode
};

class CModeApp {
public:
	virtual void input () = 0;
	virtual void run   () = 0;
	virtual void render() = 0;

	virtual void NotifyActivation  () = 0;
	virtual void NotifyDeactivation() = 0;

	virtual Mode getId() const = 0;
};