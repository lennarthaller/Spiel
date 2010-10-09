#ifndef PUNKTE_HPP
#define PUNKTE_HPP

#include <iostream>

//#define g_pPunkte CPunkte::Get()

class CPunkte
{
public:
	CPunkte();
	void ZaehlePunkte (int nPunkte);
	int GetPunkte ();

private:
	int m_nPunkte;
	
};

#endif