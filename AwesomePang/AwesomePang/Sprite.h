class CSprite {
public:
	enum Type {
		character,
		enemy,
		bullet
	};

	enum Size {
		bigSize = 128,
		midSize = 64,
		smallSize = 32
	};

	enum EOrientation {
		up,
		down,
		right,
		left
	};

	Type getSpriteType     () const;
	vec2 getSpritePosition () const;
	Size getSpriteSize     () const;
	bool getRemovableSprite() const;

	void CSprite::setSpriteType     (Type type);
	void CSprite::setSpritePosition (vec2 position);
	void CSprite::setSpriteSize     (Size size);
	void CSprite::setRemovableSprite(bool toRemove);

private:
	Type mSpriteType;
	vec2 mSpritePosition;
	Size mSpriteSize;
	bool mSpriteToDelete;
};