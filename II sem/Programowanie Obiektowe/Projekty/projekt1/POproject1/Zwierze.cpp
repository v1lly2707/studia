#include <iostream>
#include <conio.h>
#include <string>
#include <stdlib.h>

#include "Swiat.h"
#include "Zwierze.h"

using namespace std;

Zwierze::Zwierze(string ikonka, int sila, int inicjatywa, int x, int y) :Organizm(ikonka, sila, inicjatywa, x, y)
{

}

void Zwierze::kolizja(Organizm* inny)
{
	if (this == inny)
		return;

	if (typeid(*this) == typeid(*inny))
	{
		if (getWiek() < 2 || inny->getWiek() < 2)
			return;

		swiat->dodajLog(this, " Rozmnazanie");

		auto potomek = dynamic_cast<Zwierze*>(this->potomek());
		int ruch = rand() % 4;
		while (!potomek->setPozycja({ getX() + poruszanie[ruch % 4][0],getY() + poruszanie[ruch % 4][1] }, true))
		{
			ruch++;
			if (ruch > 8)
			{
				swiat->dodajLog(this, " Nie ma miejsca na rozmnozenie");
				potomek->zabijanie();
				return;
			}
		}
	}

	else if (uciekanie() || inny->uciekanie())
		return;

	else if (getSila() > inny->getSila())
	{
		//cout << "oifewhfoiwehofweoif\n";
		swiat->dodajLog(this, " Walka wygrana");
		
		inny->zabijanie();
	}

	else if (getSila() < inny->getSila())
	{
		//cout << "ihdieidehde\n";
		swiat->dodajLog(this, " Walka przegrana");
		zabijanie();
	}

	else if(getSila() == inny->getSila())
	{
		swiat->dodajLog(this, " Remis");
		
		inny->zabijanie();
	}
}

void Zwierze::akcja()
{
	postarz();
	int ruch = rand() % 4;

	while (!setPozycja({ getX() + poruszanie[ruch][0],getY() + poruszanie[ruch][1] }, false))
	{
		ruch++;
		ruch %= 4;
	}
}