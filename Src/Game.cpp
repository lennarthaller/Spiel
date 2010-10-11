

#include "Game.hpp"
#include <fstream>

// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CGame::CGame ()
{
  m_pPlayer = NULL;
  m_fSpeed = 1;
  m_bExtraAsteroid = false;
} // Konstruktor


// Init
//
// Aufgabe: Spieler, Hintergrund und Asteroid initialisieren
//
void CGame::Init ()
{
  // Neuen Spieler initialisieren
  m_pPlayer = new CPlayer;
  m_pPlayer->Init ();
  m_pPlayer->Reset ();

  // Hintergrundbild (Sprite) laden
  m_SpriteBackground.Load ("Data/Background.bmp");

  // Sprite f�r Asteroiden laden;
  m_SpriteAsteroidNormal.Load ("Data/Asteroid.bmp", 20, 64, 64);
  m_SpriteAsteroidNormal.SetColorKey (255, 0, 255);

  m_SpriteAsteroidExtra.Load ("Data/Ziffern.bmp", 10, 23, 32);
  m_SpriteAsteroidExtra.SetColorKey (255, 0, 255);

  // Timer f�r Asteroiden zur�cksetzen
  m_fAsteroidTimer = 0.0f;

  // Spiel l�uft
  m_bGameRun = true;

} // Init


// Quit
//
// Aufgabe: Instanzen freigeben
//
void CGame::Quit ()
{
	int nPunkte = m_pPlayer->GetPunkte ();
	int nHighscore = 0;
	
	ifstream Input ("Highscore.hsc", ios::binary);
	Input.read ((char*) &nHighscore, sizeof (nHighscore));
	Input.close ();
	
	if (nPunkte > nHighscore)
	{
		ofstream Output ("Highscore.hsc", ios::binary);
		Output.write ((char*) &nPunkte, sizeof (nPunkte));
		Output.close ();
	}
  
	cout << "\nsie haben " << m_pPlayer->GetPunkte () << " Punkte\n" << endl;

	// Spieler freigeben
  if (m_pPlayer != NULL)
  {

	m_AsteroidList.clear ();
   
	m_pPlayer->Quit ();
    delete (m_pPlayer);
    m_pPlayer = NULL ;
  }

} // Quit


// Run
//
// Aufgabe: Hauptschleife des Spiels
//
void CGame::Run ()
{
  // Hauptschleife des Spiels durchlaufen
  //
  while (m_bGameRun == true)
  {
    // Events bearbeiten
    ProcessEvents ();

    // Framework updaten und Buffer l�schen
    g_pFramework->Update ();
    g_pFramework->Clear ();

    // Hintergrundbild rendern
    m_SpriteBackground.Render ();

    // Spieler updaten und rendern
    m_pPlayer->Update ();
    m_pPlayer->Render ();

    // Neue Asteroiden hinzuf�gen
    SpawnAsteroids ();

    // Kollisionen pr�fen
    CheckCollisions ();

    // Asteroiden rendern
    RenderAsteroids ();

    // Buffer flippen
    g_pFramework->Flip ();

	if (m_pPlayer->GetPunkte() > 25)
	{
		m_fSpeed = 1.5;
	}
  }

} // Run


// ProcessEvents
//
// Aufgabe: Events bearbeiten
//
void CGame::ProcessEvents ()
{
  SDL_Event Event;

  // Gab es ein Event?
  if (SDL_PollEvent (&Event))
  {
    // Ja, also schauen welches
    switch (Event.type)
    {
      // Beenden?
      case (SDL_QUIT):
      {
        m_bGameRun = false;

      } break;

      // Wurde eine Taste gedr�ckt?
      case (SDL_KEYDOWN):
      {
        switch (Event.key.keysym.sym)
        {
          case (SDLK_ESCAPE):
          {
            // Ja, also Spiel beenden
            m_bGameRun = false;

          } break;
        }
      } break;
    }
  }

} // ProcessEvents


// SpawnAsteroids
//
// Aufgabe: Nach Ablauf einer bestimmten Zeit neuen Asteroiden erzeugen
//
void CGame::SpawnAsteroids ()
{
  // Timer f�r n�chsten Asteroiden erh�hen
  m_fAsteroidTimer += g_pTimer->GetElapsed ();

  // Wenn eine halbe Sekunde vergangen ist,
  // dann einen neuen Asteroiden erzeugen
  if (m_fAsteroidTimer >= 0.5f)
  {
    // Neuer Asteroid
    CAsteroid Asteroid;

    // Zuf�llige X-Position
    int XPos = rand()%736;

    // Asteroid initialisieren
	if (m_bExtraAsteroid)
	{
		Asteroid.Init (&m_SpriteAsteroidExtra, static_cast<float>(XPos), -60.0f, 10);
		m_bExtraAsteroid = false;
	}
	else
	{
		Asteroid.Init (&m_SpriteAsteroidNormal, static_cast<float>(XPos), -60.0f, 2);
	}
    
	// Asteroid in Liste einf�gen
    m_AsteroidList.push_back (Asteroid);

    // Zeitgeber wieder zur�cksetzen
    m_fAsteroidTimer = 0.0f;

  }

} // SpawnAsteroids


// CheckCollisions
//
// Aufgabe: Kollisionen zwischen Asteroiden und Sch�ssen pr�fen
//
void CGame::CheckCollisions ()
{
  // Schussliste des Spielers holen
  list<CShot> *ShotList = m_pPlayer->GetShotList ();

  // Iteratoren f�r Asteroiden- und Schussliste
  list<CAsteroid>::iterator ItAsteroid = m_AsteroidList.begin ();
  list<CShot>::iterator ItShot;

  // Rects f�r Asteroiden und Sch�sse
  SDL_Rect RectAsteroid;
  SDL_Rect RectShot;

  SDL_Rect RectPlayer = m_pPlayer->GetRect();

  // Alle Asteroiden durchlaufen
  while (ItAsteroid != m_AsteroidList.end () )
  {
    // Rect des Asteroiden holen
    RectAsteroid = ItAsteroid->GetRect ();

	// �berschneiden sich die Rects?
    if (RectPlayer.y < RectAsteroid.y + RectAsteroid.h &&
        RectPlayer.y + RectPlayer.h > RectAsteroid.y &&
        RectPlayer.x < RectAsteroid.x + RectAsteroid.w &&
        RectPlayer.x + RectPlayer.w > RectAsteroid.x)
	{
		ItAsteroid->SetAlive (false);

		bool GameOver = m_pPlayer->SpielerGetroffen ();
		
		if (GameOver)
		{
		  m_bGameRun = false;
		}

	}
	else
	{
		// Alle Sch�sse durchlaufen
		for (ItShot = ShotList->begin (); 
			 ItShot != ShotList->end ();
			 ++ItShot)
		{
		  // Rect des Schusses holen
		  RectShot = ItShot->GetRect ();

		  // �berschneiden sich die Rects?
		  if (RectShot.y < RectAsteroid.y + RectAsteroid.h &&
			  RectShot.y + RectShot.h > RectAsteroid.y &&
			  RectShot.x < RectAsteroid.x + RectAsteroid.w &&
			  RectShot.x + RectShot.w > RectAsteroid.x)
		  {
			// Ja, also gab es eine Kollision. Somit Schuss und
			// Asteroid deaktivieren
			ItAsteroid->SetAlive (false);
			ItShot->SetAlive (false);
		
			//Aufruf der funktion "funktion" zum z�hlen der punkte
			int nAlterPStand = m_pPlayer->GetPunkte();
			
			m_pPlayer->ZaehlePunkte(ItAsteroid->GetPunkteWert());
			
			if (nAlterPStand < 10 && m_pPlayer->GetPunkte() >= 10)
			{
				m_bExtraAsteroid = true;
			}
		  }
		}
	}

    // Asteroid l�schen, falls deaktiviert
    if (ItAsteroid->IsAlive () )
      ItAsteroid++;
    else
      ItAsteroid = m_AsteroidList.erase (ItAsteroid);

  }

} // CheckCollision


// RenderAsteroids
//
// Aufgabe: Alle Asteroiden rendern und updaten
//
void CGame::RenderAsteroids ()
{
  // Iterator f�r die Asteroiden-Liste
  list<CAsteroid>::iterator It;

  // Asteroiden-Liste durchlaufen
  for (It = m_AsteroidList.begin (); It != m_AsteroidList.end (); ++It)
  {
    // Asteroid rendern
    It->Render ();

    // Asteroid updaten
    It->Update (m_fSpeed);
	if (It->LostAsteroid ())
		m_pPlayer->ZaehlePunkte(-1);
  }

} // RenderAsteroids
