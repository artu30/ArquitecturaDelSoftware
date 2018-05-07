// Base class
class CMessage {
public:
	enum TType {
		ERendereable,
		ESetRemovable,
		EGetRemovable,
		EGetOrientationInX,
		EGetOrientationInY,
		ESetOrientationInX,
		ESetOrientationInY
	};

	CMessage(TType type) { mType = type; }

	TType getType() const { return mType; }

private:
	TType mType;
};

// Derived classes
class CMessageRendereable : public CMessage {
public:
	CMessageRendereable() : CMessage(ERendereable) { }
};

class CMessageSetRemovable : public CMessage {
public:
	CMessageSetRemovable() : CMessage(ESetRemovable) { }
};

class CMessageGetRemovable : public CMessage{
public:
	CMessageGetRemovable() : CMessage(EGetRemovable) { }

	void setRemovable(bool removable) { mRemovable = removable; }

	bool getRemovable() const { return mRemovable; }
private:
	bool mRemovable;
};

class CMessageGetOrientationInX : public CMessage {
public:
	CMessageGetOrientationInX() : CMessage(EGetOrientationInX) { }

	void setOrientationInX(const CSprite::EOrientation &orientationInX) { mComponentOrientationInX = orientationInX; }

	const CSprite::EOrientation& getOrientationInX() const { return mComponentOrientationInX; }
private:
	CSprite::EOrientation mComponentOrientationInX;
};

class CMessageGetOrientationInY : public CMessage {
public:
	CMessageGetOrientationInY() : CMessage(EGetOrientationInY) { }

	void setOrientationInY(const CSprite::EOrientation &orientationInY) { mComponentOrientationInY = orientationInY; }

	const CSprite::EOrientation& getOrientationInY() const { return mComponentOrientationInY; }
private:
	CSprite::EOrientation mComponentOrientationInY;
};

class CMessageSetOrientationInX : public CMessage {
public:
	CMessageSetOrientationInX() : CMessage(ESetOrientationInX) { }

	void setOrientationInX(const CSprite::EOrientation &orientationInX) { mComponentOrientationInX = orientationInX; }

	const CSprite::EOrientation& getOrientationInX() const { return mComponentOrientationInX; }
private:
	CSprite::EOrientation mComponentOrientationInX;
};

class CMessageSetOrientationInY : public CMessage {
public:
	CMessageSetOrientationInY() : CMessage(ESetOrientationInY) { }

	void setOrientationInY(const CSprite::EOrientation &orientationInY) { mComponentOrientationInY = orientationInY; }

	const CSprite::EOrientation& getOrientationInY() const { return mComponentOrientationInY; }
private:
	CSprite::EOrientation mComponentOrientationInY;
};