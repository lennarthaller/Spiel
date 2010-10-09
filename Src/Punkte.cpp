#include "Punkte.hpp"
#include <iostream>

using namespace std;

CPunkte::CPunkte ()
{
	m_Punktestand = 0;
}

// Load
//
// Aufgabe: Animiertes Sprite laden
//
void CPunkte::Load (int Startpunkte)
{

  // Rect für Animationsphase initialisieren
  m_Punktestand  = Startpunkte;

} // Load

void CPunkte::m_zaehlePunkte ()
{
	m_Punktestand ++;
}

void CPunkte::m_zeigePunkte ()
{
	cout << "sie haben " << m_Punktestand << " Asteroiden abgeschossen!" << endl;
	cin >> buchstabe;
}
