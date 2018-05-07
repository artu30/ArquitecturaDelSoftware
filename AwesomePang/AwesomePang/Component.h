class CEntity;

// Base class
class CComponent {
public:
	CComponent(CEntity* pOwner) { mOwner = pOwner; }

	virtual void update        ()              = 0;
	virtual void receiveMessage(CMessage &msg) = 0;
	
	CEntity* getOwner() const { return mOwner; }

private:
	CEntity* mOwner;
};

// Derived classes
class CComponentRendereable : public CComponent {
public:
	CComponentRendereable(CEntity *pOwner) : CComponent(pOwner) { }

	void update        ();
	void receiveMessage(CMessage &msg);
};

class CComponentRemovable : public CComponent {
public:
	CComponentRemovable(CEntity *pOwner) : CComponent(pOwner) { mRemovable = false; }

	void update        ();
	void receiveMessage(CMessage &msg);

	bool getRemovable() const         { return mRemovable; }
	void setRemovable(bool removable) { mRemovable = removable; }
	
private:
	bool mRemovable;
};

class CComponentElementOrientation : public CComponent {
public:
	CComponentElementOrientation(CEntity *pOwner) : CComponent(pOwner) { }

	void update        ();
	void receiveMessage(CMessage &msg);

	CSprite::EOrientation getOrientationInX() const { return mComponentOrientationInX; }
	CSprite::EOrientation getOrientationInY() const { return mComponentOrientationInY; }

	void setOrientationInX(CSprite::EOrientation xOrientation) { mComponentOrientationInX = xOrientation; }
	void setOrientationInY(CSprite::EOrientation yOrientation) { mComponentOrientationInY = yOrientation; }

private:
	CSprite::EOrientation mComponentOrientationInX;
	CSprite::EOrientation mComponentOrientationInY;
};

class CComponentInertialMovement : public CComponent {
public:
	CComponentInertialMovement(CEntity *pOwner) : CComponent(pOwner) { }

	void update        ();
	void receiveMessage(CMessage &msg) { }
};