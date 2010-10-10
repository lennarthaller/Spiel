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
    CSprite  m_SpriteBackground;   // Sprite für den Hintergrund
    CSprite  m_SpriteAsteroidNormal; // Sprite für die Asteroiden
	CSprite  m_SpriteAsteroidExtra; 
    float    m_fAsteroidTimer;      // Zeitgeber für nächsten Asteroiden
    bool     m_bGameRun;            // Läuft das Spiel noch?
    list<CAsteroid> m_AsteroidList; // Liste der Asteroiden
	float    m_fSpeed;
	bool     m_bExtraAsteroid;

};

#endif
