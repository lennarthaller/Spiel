#include "Framework.hpp"
#include "Game.hpp"
#include "Punkte.hpp"
#include "Player.hpp"

using namespace std;

int main (int argc, char *argv[])
{

  // Framework initialisieren
  if (g_pFramework->Init (800, 600, 16, true) == false)
    return (0);
  
  // Neue Instanz des Spiels
   CGame Game;

  // Spiel initialisieren
  Game.Init ();

  // Spiel laufen lassen. Diese Funktion läuft so lange,
  // bis das Spiel geschlossen oder die Escape-Taste
  // gedrückt wird
  Game.Run ();

  // Spiel beenden
  Game.Quit ();

  //m_pSpielerpunkte->m_zeigePunkte ();
  		//Punkte anzeigen
	    CPunkte::Get()->m_zeigePunkte();
 
  // Framework beenden
  g_pFramework->Quit ();
  g_pFramework->Del ();

  return (0);

}
