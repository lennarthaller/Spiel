#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include "Sprite.hpp"
#include "Shot.hpp"
#include "Punkte.hpp"
#include "NumberDisplay.hpp"

class CPlayer
{
  public:
    CPlayer     ();

    void Init   ();
    void Quit   ();
    void Render ();
    void Update ();
    void Reset  ();
    list<CShot> *GetShotList () {return &m_ShotList;}
	SDL_Rect GetRect ();
	bool SpielerGetroffen ();
	void ZaehlePunkte (int nPunkte);
	int GetPunkte ();

  private:
    void ProcessMoving   ();
    void ProcessShooting ();
    void CheckPosition   ();
	
    CSprite *m_pSpritePlayer;  // Sprite für Spieler
    CSprite *m_pSpriteShot;    // Sprite für Laserschüsse
    float m_fXPos;             // X-Position des Spielers
    float m_fYPos;             // Y-Position des Spielers
    float m_fAnimPhase;       // Aktuelle Animationsphase
    bool m_bShotLock;         // Darf der nächste Schuss raus?
    list<CShot> m_ShotList;   // Liste der Schüsse
	int m_nLeben;
	CPunkte m_Punkte;
	CNumberDisplay m_PunkteDisplay;
	CNumberDisplay m_LebenDisplay;
	int m_nTimeStampOfExplosion;
};

#endif
