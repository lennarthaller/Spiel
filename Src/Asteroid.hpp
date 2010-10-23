#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Sprite.hpp"

class CAsteroid
{
  public:
    void Init     (CSprite *pSpriteAsteroid, float fXPos, float fYPos, int nPunktWert, float fXSpeed, float fYSpeed, int XRichtung, int YRichtung);
  //  void Update   (float XSpeed, float YSpeed, int YRichtungWechsel, int XRichtungWechsel);
    void Update   ();
    void Render   ();
    bool IsAlive  () {return m_bIsAlive;}
    void SetAlive (bool bIsAlive) {m_bIsAlive = bIsAlive;}
    SDL_Rect GetRect () {return m_Rect;}
	bool LostAsteroid () {return m_bLostAsteroid;}
	int GetPunkteWert () {return m_nPunktWert;}

  private:
	bool m_bLostAsteroid;
    CSprite *m_pSpriteAsteroid; // Zeiger auf Asteroiden-Sprite
    float    m_fXPos;           // X-Position des Asteroiden
    float    m_fYPos;           // Y-Position des Asteroiden
    float    m_fAnimPhase;      // Akt. Animationsphase des Asteroiden
    bool     m_bIsAlive;        // "Lebt" der Asteroid noch?
    SDL_Rect m_Rect;            // Rect des Asteroiden
	int      m_nPunktWert;
	float	 m_fXSpeed;
	float	 m_fYSpeed;
	int		 m_nXRichtung;
	int		 m_nYRichtung;
};

#endif
