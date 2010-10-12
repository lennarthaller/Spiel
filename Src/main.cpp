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
	
  // Spiel laufen lassen. Diese Funktion l�uft so lange,
  // bis das Spiel geschlossen oder die Escape-Taste
  // gedr�ckt wird
   int highscore = 0;
   int nKeinePunkte = 0;

	do
	{
	cout << "Asteroids - Menue" << endl;
	cout << "-----------------" << endl;
	cout << "(N)eus Spiel starten" << endl;
	cout << "(H)ighscore anzeigen" << endl;
	cout << "(L)Highscore loeschen" << endl;
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
					cout << "Es gibt noch keinen Highscore" << endl;
			} else {
				Input.read ((char*) &highscore, sizeof (highscore));
				Input.close ();
				cout << "\nDer Highscore ist: ";
				cout << highscore << endl << endl;
			}
		} break;

		case ('I'):
		case ('i'): {
			cout << "\nAsteroids v2.3\n";
			cout << "Copyright Lennart Haller\n\n";
					} break;
		
		case ('L'):
		case ('l'): {

			ifstream Input ("Highscore.hsc", ios::binary);
			ofstream Output ("Highscore.hsc", ios::binary);
			Output.write ((char*) &nKeinePunkte, sizeof (nKeinePunkte));
			Output.close ();
			cout << "\nHighscore geloescht\n" << endl;
					} break;
		
		default:

	{
		cout << "Falsche Eingabe!\n\n";
	}
   }
    } while (auswahl != 'b' && auswahl != 'B');
	
	cout << "Bis zum n�chsten Mal" << endl;

				
		return 0;
}

