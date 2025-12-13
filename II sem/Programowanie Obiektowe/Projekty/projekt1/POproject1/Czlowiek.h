#pragma once
#include "Zwierze.h"

class Czlowiek :


	public Zwierze
{
private:

	int umiejetnosc;
	pair < int, int > XY;
	bool czyNiesmiertelny;
	int sila;
	int inicjatywa;
	pair < int, int > pozycja;

	const int poruszanie[8][2] =
	{
		{0,2},
		{2,0},
		{0,-2},
		{-2,0},
		{1,1},
		{1,-1},
		{-1,1},
		{-1,-1},
	};


public:

	Czlowiek(int x, int y);
	bool ucieczka();
	void akcja();
	bool setXY(pair < int, int > XY);
	void aktywujUm();
	void setUm(int umiejetnosc);
	string toString();
	Czlowiek* potomek();
	virtual void zabijanie() override;
};