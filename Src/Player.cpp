#include "Player.hpp"

// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CPlayer::CPlayer ()
{
  m_pSpritePlayer = NULL;
  m_pSpriteShot = NULL;

} // Konstruktor


// Init
//
// Aufgabe: Sprites erzeugen und laden
//
void CPlayer::Init ()
{
	m_nLeben = 3;
	m_LebenDisplay.SetScreenPosition(89, 20);
	m_LebenDisplay.SetNumber(m_nLeben);
	m_PunkteDisplay.SetScreenPosition(734, 20);
	m_PunkteDisplay.SetNumber(GetPunkte());

  // Spielersprite erstellen
  m_pSpritePlayer = new CSprite;

  m_pSpritePlayer->Load ("Data/Player.bmp", 11, 64,64);
  m_pSpritePlayer->SetColorKey (255, 0, 255);

  // Schuss-Sprite erstellen
  m_pSpriteShot = new CSprite;

  m_pSpriteShot->Load ("Data/Laser.bmp", 0, 64, 64);
  m_pSpriteShot->SetColorKey (255, 0, 255);

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

// Render
//
// Aufgabe: Spieler und Sch�sse rendern
//
void CPlayer::Render ()
{
  // Position des Spielers setzen und Sprite rendern
  m_pSpritePlayer->SetPos (m_fXPos, m_fYPos);
  m_pSpritePlayer->Render (m_fAnimPhase);
 
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
		ZaehlePunkte (-10);

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
  // Nach links?
  if (g_pFramework->KeyDown (SDLK_LEFT))
  {
    // Spieler nach links bewegen
    m_fXPos -= 300.0f * g_pTimer->GetElapsed ();

    // Animieren
    m_fAnimPhase -= 20.0f * g_pTimer->GetElapsed ();

  }
  // Nach rechts?
  else if (g_pFramework->KeyDown (SDLK_RIGHT))
  {
    // Spieler nach rechts bewegen
    m_fXPos += 300.0f * g_pTimer->GetElapsed ();

    // Animieren
    m_fAnimPhase += 20.0f * g_pTimer->GetElapsed ();

  }
  
  // Nach oben?
  else if (g_pFramework->KeyDown (SDLK_UP))
  {
    // Spieler nach oben bewegen
    m_fYPos -= 300.0f * g_pTimer->GetElapsed ();

  }

  
  // Nach unten?
  else if (g_pFramework->KeyDown (SDLK_DOWN))
  {
    // Spieler nach unten bewegen
    m_fYPos += 300.0f * g_pTimer->GetElapsed ();

  }
 
  // Spieler wurde nicht bewegt
  else
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
    m_fXPos = 0.0f;
  else if (m_fXPos > 752.0f)
    m_fXPos = 752.0f;

  // Animationsphase pr�fen
  if (m_fAnimPhase < 0.0f)
    m_fAnimPhase = 0.0f;
  else if (m_fAnimPhase > 10.0f)
    m_fAnimPhase = 10.0f;

} // CheckPosition
