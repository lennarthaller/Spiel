#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Asteroid.hpp"

//int punkte = 0;

class CGame
{
  public:
    CGame ();

    void Init ();
    void Run  ();
    void Quit ();
	void testepunkte();

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
	float    m_fSpeed;
	bool     m_bExtraAsteroid;

};

#endif
