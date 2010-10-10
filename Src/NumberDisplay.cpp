#include <iostream>
#include "NumberDisplay.hpp"

CZifferSprite::CZifferSprite (int nZiffer, int Position_x, int Position_y)
{
	m_nZiffer = nZiffer;
	m_Sprite.Load("Data/ziffern.bmp", 10, 23, 32);
	m_Sprite.SetColorKey (255, 0, 255);
	m_Sprite.SetPos      (Position_x, Position_y);
}

void CZifferSprite::Render ()
{
	m_Sprite.Render (m_nZiffer);
}

CNumberDisplay::CNumberDisplay ()
{
	m_Position_x = -1;
	m_Position_y = -1;
}


void CNumberDisplay::SetNumber(int Number)
{	
	for (std::list<CZifferSprite*>::iterator it = m_ZifferSprites.begin(); it != m_ZifferSprites.end(); it++)
	{
		delete *it;
	}

	m_ZifferSprites.clear();
	
	if (m_Position_x < 0 && m_Position_y < 0)
	{
		return;
	}

	int Position_x = m_Position_x;
	
	do 
	{
		int nZiffer;
		nZiffer =  Number % 10;

		Position_x -= 23;

		CZifferSprite *sprite = new CZifferSprite(nZiffer, Position_x, m_Position_y);

		m_ZifferSprites.push_front(sprite);

		Number /= 10;
	}
	while ( Number != 0);
}

void CNumberDisplay::SetScreenPosition(int x, int y)
{
	m_Position_x = x;
	m_Position_y = y;
}

void CNumberDisplay::Render ()
{
	for (std::list<CZifferSprite*>::iterator it = m_ZifferSprites.begin(); it != m_ZifferSprites.end(); it++)
	{
		(*it)->Render();
	}
}
