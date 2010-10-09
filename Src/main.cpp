  #include "Framework.hpp"
  #include "Game.hpp"
  #include "Punkte.hpp"
  #include "Player.hpp"
  #include <iostream>
  #include <fstream>

using namespace std;

int main (int argc, char *argv[])
{
	char auswahl;

  // Framework initialisieren

  // Neue Instanz des Spiels
	
  // Spiel initialisieren
	
  // Spiel laufen lassen. Diese Funktion läuft so lange,
  // bis das Spiel geschlossen oder die Escape-Taste
  // gedrückt wird
   int highscore = 0;
  	
	do
	{
	cout << "Asteroids - Menue" << endl;
	cout << "-----------------" << endl;
	cout << "(N)eus Spiel starten" << endl;
	cout << "(H)ighscore anzeigen" << endl;
	cout << "(I)nfo" << endl;
	cout << "(B)eenden\n\n";
//Abfrage
	cout << "Auswahl ";
	cin >> auswahl;

	switch (auswahl) {
	
		case ('N'):
		case ('n'):  {
			bool Success = g_pFramework->Init (800, 600, 16, false);
			if (!Success)
				return (0);
			CGame Game;
			Game.Init ();
			Game.Run ();

			// Spiel beenden
			Game.Quit ();


 
		  // Framework beenden
			g_pFramework->Quit ();
			g_pFramework->Del ();
		} break;
		
		case ('H'):
		case ('h'): {
			
			ifstream Input ("Highscore.hsc", ios::binary);
			if (Input == NULL) {
					cout << "Datei konnte nicht geoefnet werden" << endl;
			} else {
				Input.read ((char*) &highscore, sizeof (highscore));
				Input.close ();
				cout << "Der Highscore ist: ";
				cout << highscore << endl;
			}
		} break;

		case ('I'):
		case ('i'): {
			cout << "\nAsteroids v1.0\n";
			cout << "Copyright Lennart Haller\n\n";
					} break;
		
		
		
		
		default:

	{
		cout << "Falsche Eingabe!\n\n";
	}
   }
    } while (auswahl != 'b' && auswahl != 'B');
	
	cout << "Bis zum nächsten Mal" << endl;

				
		return 0;
}

