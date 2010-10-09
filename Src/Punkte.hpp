#ifndef PUNKTE_HPP
#define PUNKTE_HPP

#include <iostream>
#include "Singleton.hpp"

using namespace std;

//#define g_pPunkte CPunkte::Get()

class CPunkte : public TSingleton<CPunkte>
{
	private:
	
	//Membervariablen
	int m_Punktestand;
	char buchstabe;
	
	public:
	//Memberfunktionen

	CPunkte ();
	void Load (int Startpunkte);
	void m_zaehlePunkte ();
	void m_zeigePunkte ();
};

#endif