#include "Asteroid.hpp"

// Init
//
// Aufgabe: Asteroid initialisieren
//
void CAsteroid::Init (CSprite *pSpriteAsteroid, float fXPos, float fYPos, int nPunktWert, float fXSpeed, float fYSpeed, int YRichtung, int XRichtung)
{
  // Zeiger auf Sprite kopieren und Koordinaten setzen
  m_pSpriteAsteroid = pSpriteAsteroid;
  m_fXPos = fXPos;
  m_fYPos = fYPos;
  m_nPunktWert = nPunktWert;
  m_fXSpeed = fXSpeed;
  m_fYSpeed = fYSpeed;
  m_nXRichtung = XRichtung;
  m_nYRichtung = YRichtung;

  // Animation beginnt beim ersten Einzelbild
  m_fAnimPhase = 0.0f;

  // Rect initialisieren
  m_Rect.x = static_cast<int>(fXPos);
  m_Rect.y = static_cast<int>(fYPos);
  m_Rect.w = pSpriteAsteroid->GetRect().w;
  m_Rect.h = pSpriteAsteroid->GetRect().h;

  // Asteroid aktivieren
  m_bIsAlive = true;

} // Init


// Update
//
// Aufgabe: Asteroid bewegen und Position prüfen
//
//void CAsteroid::Update (float XSpeed, float YSpeed, int YRichtungWechsel, int XRichtungWechsel)
void CAsteroid::Update ()
{
  m_bLostAsteroid = false;

 // m_nXRichtung *= XRichtungWechsel;
 // m_nYRichtung *= YRichtungWechsel;

  // Asteroid bewegen
  m_fYPos += 200.0f * g_pTimer->GetElapsed () * m_fYSpeed * m_nYRichtung;

  m_fXPos += 200.0f * g_pTimer->GetElapsed () * m_fXSpeed * m_nXRichtung;

  m_Rect.y = static_cast<int>(m_fYPos);

  m_Rect.x = static_cast<int>(m_fXPos);

  // Animieren
  m_fAnimPhase += 10.0f * g_pTimer->GetElapsed ();

  // Prüfen, ob die Animation am Ende angelangt ist
  int NumFrames = m_pSpriteAsteroid->GetNumFrames();
 
  if (m_fAnimPhase >= NumFrames)
    m_fAnimPhase = m_fAnimPhase - NumFrames;

  if (m_fYPos < 9)
  { 
	  m_nYRichtung = 1; 
  }
  else 
  // Deaktivieren, falls außerhalb des Bildschirms
  if ((m_fYPos > 590.0f) || (m_fYPos < 10.0f))
  {
		   m_nYRichtung *= -1; 
   // m_bIsAlive = false;
   //m_bLostAsteroid = true;
  }

  if ((m_fXPos > 790.0f) || (m_fXPos < 10.0f))
//  m_fXPos = 0.0f;
   m_nXRichtung *= -1; 

} // Update


// Render
//
// Aufgabe: Asteroid rendern
//
void CAsteroid::Render ()
{
  m_pSpriteAsteroid->SetPos (m_fXPos, m_fYPos);
  m_pSpriteAsteroid->Render (m_fAnimPhase);

} // Render
