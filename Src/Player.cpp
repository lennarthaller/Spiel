#include "Player.hpp"

// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CPlayer::CPlayer ()
{
  m_pSpritePlayer = NULL;
  m_pSpriteShot = NULL;
  m_nTimeStampOfExplosion = -1;
  m_nTreffer = 0;
  m_nDanebengeschossen = 0;
} // Konstruktor


// Init
//
// Aufgabe: Sprites erzeugen und laden
//
void CPlayer::Init ()
{
  m_nTreffer = 0;
	m_nLeben = 3;
	m_LebenDisplay.SetScreenPosition(89, 20);
	m_LebenDisplay.SetNumber(m_nLeben);
	m_PunkteDisplay.SetScreenPosition(734, 20);
	m_PunkteDisplay.SetNumber(GetPunkte());

  // Spielersprite erstellen
  m_pSpritePlayer = new CSprite;

  m_pSpritePlayer->Load ("Data/Player.bmp", 12, 64,64);
  m_pSpritePlayer->SetColorKey (255, 0, 255);

  // Schuss-Sprite erstellen
  m_pSpriteShot = new CSprite;

  m_pSpriteShot->Load ("Data/Laser2.bmp", 0, 20, 100);
  m_pSpriteShot->SetColorKey (0, 0, 0);

} // Init


// Quit
//
// Aufgabe: Sprites freigeben
//
void CPlayer::Quit ()
{
  // Spieler-Sprite freigeben
  if (m_pSpritePlayer != NULL)
  {
    delete (m_pSpritePlayer);
    m_pSpritePlayer = NULL;
  }

  // Schuss-Sprite freigeben
  if (m_pSpritePlayer != NULL)
  {
    delete (m_pSpritePlayer);
    m_pSpritePlayer = NULL;
  }

} // Quit


// Reset
//
// Aufgabe: Spielerwerte auf Standard setzen
//
void CPlayer::Reset ()
{
  // Startposition des Spielers
  m_fXPos = 376.0f;
  m_fYPos = 520.0f;

  // Animationsphase
  m_fAnimPhase = 5.0f;

  // Es darf geschossen werden
  m_bShotLock = false;

} // Reset

SDL_Rect CPlayer::GetRect ()
{
	return m_pSpritePlayer->GetRect ();	
}

bool CPlayer::SpielerGetroffen ()
{
  m_nTimeStampOfExplosion = SDL_GetTicks();

  m_nLeben --;
  
  m_LebenDisplay.SetNumber(m_nLeben);

  if ( m_nLeben == 0)
  {
	return true;
  }
  return false;
}

void CPlayer::ZaehlePunkte (int nPunkte)
{
	m_Punkte.ZaehlePunkte (nPunkte);
	m_PunkteDisplay.SetNumber(GetPunkte());
}

int CPlayer::GetPunkte ()
{
	return m_Punkte.GetPunkte ();
}

void CPlayer::SetTreffer ()
{
	m_nTreffer ++;
}

// Render
//
// Aufgabe: Spieler und Sch�sse rendern
//
void CPlayer::Render ()
{
  // Position des Spielers setzen und Sprite rendern
  m_pSpritePlayer->SetPos (m_fXPos, m_fYPos);
  if (m_nTimeStampOfExplosion != -1)
  {
	  int nVergangeneZeit = SDL_GetTicks() - m_nTimeStampOfExplosion;
	 
	  if (nVergangeneZeit > 500)
	  {  
		m_nTimeStampOfExplosion = -1;
	  }
	 m_pSpritePlayer->Render (11);
	 
  }
  else
  {
	  m_pSpritePlayer->Render (m_fAnimPhase);
  }
 
  m_PunkteDisplay.Render ();
  m_LebenDisplay.Render ();

  // Iterator f�r Schussliste
  list<CShot>::iterator it = m_ShotList.begin ();

  // Schussliste durchlaufen
  while (it != m_ShotList.end ())
  {
    // Schuss updaten
    it->Update ();

	if (it->bWastedShot)
	{
		ZaehlePunkte (-10);
		m_nDanebengeschossen ++;
	}

    // Ist der Schuss noch aktiv?
    if (it->IsAlive ())
    {
      // Ja, dann rendern
      it->Render ();
      it++;
    }
    else
    {
      // Nein, dann aus der Liste entfernen
      it = m_ShotList.erase (it);
    }

  }

} // Render


// Update
//
// Aufgabe: Spieler updaten
//
void CPlayer::Update ()
{
  // Bewegung des Spielers
  ProcessMoving ();

  // Pr�fen, ob geschossen wurde
  ProcessShooting ();

  // Position und Animationsphase �berpr�fen
  CheckPosition ();

} // Update


// ProcessMoving
//
// Aufgabe: Bewegung des Spielers
//
void CPlayer::ProcessMoving ()
{
  bool bHasMoved = false;

  // Nach links?
  if (g_pFramework->KeyDown (SDLK_LEFT))
  {
    // Spieler nach links bewegen
    m_fXPos -= 500.0f * g_pTimer->GetElapsed ();

    // Animieren
    m_fAnimPhase -= 20.0f * g_pTimer->GetElapsed ();

	bHasMoved = true;
  }
  // Nach rechts?
  if (g_pFramework->KeyDown (SDLK_RIGHT))
  {
    // Spieler nach rechts bewegen
    m_fXPos += 500.0f * g_pTimer->GetElapsed ();

    // Animieren
    m_fAnimPhase += 20.0f * g_pTimer->GetElapsed ();

	bHasMoved = true;
  }
  
  // Nach oben?
  if (g_pFramework->KeyDown (SDLK_UP))
  {
    // Spieler nach oben bewegen
    m_fYPos -= 500.0f * g_pTimer->GetElapsed ();

	bHasMoved = true;
  }

  
  // Nach unten?
  if (g_pFramework->KeyDown (SDLK_DOWN))
  {
    // Spieler nach unten bewegen
    m_fYPos += 500.0f * g_pTimer->GetElapsed ();

	bHasMoved = true;
  }
 
  // Spieler wurde nicht bewegt
  if (!bHasMoved)
  {
    // Animation zur�ck zum Ausgangspunkt
    if (m_fAnimPhase > 5.0f)
      m_fAnimPhase -= 20.0f * g_pTimer->GetElapsed ();

    if (m_fAnimPhase < 5.0f)
      m_fAnimPhase += 20.0f * g_pTimer->GetElapsed ();
  }

} // ProcessMoving


// ProcessShooting
//
// Aufgabe: Waffe abfeuern
//
void CPlayer::ProcessShooting ()
{
  // Wurde Space gedr�ckt und darf geschossen werden?
  if (g_pFramework->KeyDown (SDLK_SPACE) && m_bShotLock == false)
  {
    // Neuen Schuss erzeugen und initialisieren
    CShot Shot;

    Shot.Init (m_pSpriteShot, m_fXPos, m_fYPos);

    // Schuss in Liste einf�gen
    m_ShotList.push_back (Shot);

    // Schie�en erst wieder erlaubt, wenn Space losgelassen
    m_bShotLock = true;

  }

  // Ist die Leertaste nicht mehr gedr�ckt, schie�en wieder erlaubt
  if (g_pFramework->KeyDown (SDLK_SPACE) == false)
    m_bShotLock = false;

} // ProcessShooting


// CheckPosition
//
// Aufgabe: Position und Animationsphase pr�fen
//
void CPlayer::CheckPosition ()
{
  // Linker und rechter Rand
  if (m_fXPos < 0.0f)
    m_fXPos = 752.0f;
  else if (m_fXPos > 752.0f)
    m_fXPos = 0.0f;
  
    if (m_fYPos < 0.0f)
    m_fYPos = 542.0;
  else if (m_fYPos > 542.0f)
    m_fYPos = 0.0f;


  // Animationsphase pr�fen
  if (m_fAnimPhase < 0.0f)
    m_fAnimPhase = 0.0f;
  else if (m_fAnimPhase > 10.0f)
    m_fAnimPhase = 10.0f;

} // CheckPosition
