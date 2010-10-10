#include <list>
#include "Sprite.hpp"

class CZifferSprite
{
public:
	CZifferSprite (int nZiffer, int Position_x, int Position_y);
	void Render ();
private:
	int m_nZiffer;
	CSprite m_Sprite;
};

class CNumberDisplay
{
public:
	CNumberDisplay ();
	void SetNumber(int Number);
	void SetScreenPosition(int x, int y);
	void Render ();

private:
	std::list<CZifferSprite*> m_ZifferSprites;
	int m_Position_x, m_Position_y;
};

