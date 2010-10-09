#include "Punkte.hpp"
#include <iostream>

CPunkte::CPunkte ()
{
	m_nPunkte = 0;
}

void CPunkte::ZaehlePunkte (int Punkte)
{
	m_nPunkte += Punkte;
}

int CPunkte::GetPunkte ()
{
	return m_nPunkte;
}
