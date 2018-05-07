class CEntity {
public:
	~CEntity();

	vec2 getEntityPosition() const;
	void setEntityPosition(vec2 position);

	CSprite*      getEntitySprite() const;
	CSprite::Type getEntityType  () const;
	CSprite::Size getEntitySize  () const;

	void setEntitySprite(CSprite* sprite);
	void setEntityType  (CSprite::Type type);
	void setEntitySize  (CSprite::Size size);
	
	void update();

	void AddComponent(CComponent* component);

	void manageMessage(CMessage* pMsg);

private:
	vec2                     mEntityPosition;
	CSprite*                 mEntitySprite;
	std::vector<CComponent*> mComponents;
	CSprite::Type			 mEntityType;
	CSprite::Size			 mEntitySize;
};