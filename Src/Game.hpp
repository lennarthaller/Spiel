#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Asteroid.hpp"


class CGame
{
  public:
    CGame ();

    void Init ();
    void Run  ();
    void Quit ();
	void testepunkte();
	void ZaeleDanebenGeschossen ();
//	void GetLevel() {return m_nLevel;}

  private:
    void ProcessEvents   ();
    void SpawnAsteroids  ();
    void RenderAsteroids ();
    void CheckCollisions  ();

    CPlayer *m_pPlayer;             // Spieler-Instanz
    CSprite  m_SpriteBackground;   // Sprite f�r den Hintergrund
    CSprite  m_SpriteAsteroidNormal; // Sprite f�r die Asteroiden
	CSprite  m_SpriteAsteroidExtra; 
    float    m_fAsteroidTimer;      // Zeitgeber f�r n�chsten Asteroiden
    bool     m_bGameRun;            // L�uft das Spiel noch?
    list<CAsteroid> m_AsteroidList; // Liste der Asteroiden
	float    m_fXAsteroidSpeed;
	float    m_fYAsteroidSpeed;
	bool     m_bExtraAsteroid;
	int		 m_nLevel;
	

};

#endif
