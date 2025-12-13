#include "Swiat.h"
#include "Czlowiek.h"

Czlowiek::Czlowiek(int x, int y) : Zwierze(EMOJI ? u8"Cz" : "Cz", 5, 4, x, y)
{
	umiejetnosc = -5;
	XY = { 0,0 };
}

void Czlowiek::akcja()
{
	postarz();
	int predkosc = 1;

	if (umiejetnosc > -5)
		umiejetnosc--;

	else if (umiejetnosc == 0)
		czyNiesmiertelny = false;
	

	setPozycja({ getX() + XY.first * predkosc,getY() + XY.second * predkosc }, false);
	XY = { 0,0 };

}

bool Czlowiek::setXY(pair < int, int >XY)
{
	if ((getX() + XY.first) < 0 || (getX() + XY.first) >= swiat->getSzerokosc() || (getY() + XY.second) < 0 || (getY() + XY.second) >= swiat->getWysokosc())
		return false;

	this->XY = XY;
	return true;

}


void Czlowiek::aktywujUm()
{
	if (umiejetnosc == -5)
	{
		swiat->dodajLog(this, " Aktywowano specjalna umiejetnosc czlowieka: niesmiertelnosc\n");
		umiejetnosc = 5;
		czyNiesmiertelny = true;
	}
}

void Czlowiek::setUm(int umiejetnosc)
{
	this->umiejetnosc = umiejetnosc;

}

string Czlowiek::toString()
{
	string nowy = Zwierze::toString();
	nowy += to_string(umiejetnosc) + ';';
	return nowy;

}

void Czlowiek::zabijanie()
{
	

	if (czyNiesmiertelny == false)
	{
		pozycja = { -1, -1 };
		sila = -1;
		inicjatywa = -1;
	}
	else
	{
		int ruch = rand() % 8;
		setPozycja({ getX() + poruszanie[ruch][0], getY() + poruszanie[ruch][1] }, true);
	}
}

Czlowiek* Czlowiek::potomek()
{
	return nullptr;

}

