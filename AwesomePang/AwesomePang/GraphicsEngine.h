class CGraphicsEngine {
public:
	struct Texture {
		CSprite::Type mType;
		GLuint        mTextureId;
	};

	~CGraphicsEngine();

	void render();

	GLuint getTexture(CSprite::Type type) const;

	void addTexture   (Texture texture);
	bool removeTexture(CSprite::Type type);

	void addSprite    (CSprite* sprite);
	void removeSprites();

	int  getNumEnemies() const;
	void setNumEnemies(int enemies);

private:
	std::vector<CSprite*> mSprites;
	std::vector<Texture>  mGameTextures;
	int                   mNumEnemies;
};