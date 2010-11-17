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
			
		    int nKeinePunkte = 0;
			char JaNein;

			cout << "\nSoll der Highscore wirklich geloescht werden?" << endl;
			cout << "(J)a" << endl;
			cout << "(N)ein" << endl;
		    cin >> 	JaNein;

			if ((JaNein == 'J') || (JaNein == 'j'))
				{
			ofstream Output ("Highscore.hsc", ios::binary);
			Output.write ((char*) &nKeinePunkte, sizeof (nKeinePunkte));
			Output.close ();
			cout << "\nHighscore geloescht\n" << endl;
				}
			
			if ((JaNein == 'N') || (JaNein == 'n'))
			{
				cout << "\nHighscore wurde nicht geloescht" << endl << endl;
			}

			else
			{
				cout << "\nFalsche Eingabe" << endl << endl; 
			}
			
	
			
			
			} break;
			
		case ('p'):
			{
					float test = rand()%10;
				test /= 10;
				test += 0.5;
				cout << test << endl;
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

