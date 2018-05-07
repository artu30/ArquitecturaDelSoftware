class CItemSelectable {
public:
	std::string(*mFunction)();

	CItemSelectable(std::string reference);

	void         setReference(std::string reference);
	std::string  getReference() const;
	vec2         getPosition () const;

	void setPosition(vec2 position);
	void setFunction(std::string(*func)());

	void render(std::string text);

private:
	std::string mReference;
	vec2        mPosition;
};