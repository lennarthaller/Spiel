#include "Shot.hpp"

// Init
//
// Aufgabe: Schuss initialisieren
//
void CShot::Init (CSprite *pSpriteShot, float fXPos, float fYPos)
{
  // Zeiger auf Sprite kopieren und Koordinaten setzen
  m_pSpriteShot = pSpriteShot;
  m_fXPos = fXPos + 20;
  m_fYPos = fYPos;

  // Rect initialisieren
  m_Rect.x = static_cast<int>(fXPos);
  m_Rect.y = static_cast<int>(fYPos);
  m_Rect.w = pSpriteShot->GetRect().w;
  m_Rect.h = pSpriteShot->GetRect().h;

  // Schuss aktivieren
  m_bIsAlive = true;

} // Init


// Update
//
// Aufgabe: Schuss bewegen und Position prüfen
//
void CShot::Update ()
{ 
  int nLevel;
  bWastedShot = false;
  // Schuss bewegen
  m_fYPos -= 600.0f * g_pTimer->GetElapsed ();

  m_Rect.y = static_cast<int>(m_fYPos);

  // Deaktivieren, falls außerhalb des Bildschirms
  
//  Game->GetLevel() = nLevel;
  
  
  if (m_fYPos < -15.0f)
  {
	m_bIsAlive = false;
/*	if (nLevel  > 1)
	{
		bWastedShot = true;
	} */
  }

} // Update


// Render
//
// Aufgabe: Schuss rendern
//
void CShot::Render ()
{
  if (m_bIsAlive == true)
  {
    // Koordinaten setzen und rendern
    m_pSpriteShot->SetPos (m_fXPos, m_fYPos);
    m_pSpriteShot->Render ();
  }

} // Render
