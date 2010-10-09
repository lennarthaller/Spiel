#include <list>
#include "Sprite.hpp"

class CNumberDisplay
{
public:
	CNumberDisplay ();
	void SetNumber(int Number);
	void SetScreenPosition(int x, int y);
	void Render ();

private:
	std::list<CSprite*> m_ZifferSprites;
	int m_Position_x, m_Position_y;
};
