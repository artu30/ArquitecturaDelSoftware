class CGame {
public:
	CGame ();
	~CGame();

	void run();

	void checkCollisionBulletEnemy   ();
	void checkCollisionEnemyCharacter();

	void movePlayer    (float xMovement, CSprite::EOrientation orientation);
	void moveElements  ();
	void removeElements();

	void createBullet();

	void finishGame();

	int getCountEntitiesByType(CSprite::Type type);

	// Keys controller
	bool getSpacePressed () const;
	bool getEscapePressed() const;
	bool getPKeyPressed  () const;
	bool getPaused       () const;

	void setSpacePressed (bool pressed);
	void setEscapePressed(bool pressed);
	void setPKeyPressed  (bool pressed);
	void setPaused       (bool paused);

	// To use input from menu
	void usePauseMenuInput();

private:
	std::vector<CEntity*> mEntities;
	CEntity*			  mPlayer;
	bool                  mSpacePressedController;
	bool                  mEscapePressedController;
	bool                  mPKeyPressedController;
	bool                  mPaused;
};