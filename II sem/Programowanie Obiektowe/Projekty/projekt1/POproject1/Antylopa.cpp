#include "Swiat.h"
#include "Antylopa.h"

Antylopa::Antylopa(int x, int y) : Zwierze(EMOJI ? u8"An" : "An", 4, 4, x, y)
{

}

void Antylopa::akcja()
{
	postarz();
	int ruch = rand() % 8;

	while (!setPozycja({ getX() + poruszanie[ruch][0], getY() + poruszanie[ruch][1] }, false))
	{
		ruch++;
		ruch %= 8;

	}

}

bool Antylopa::uciekanie()
{
	bool ucieczka = rand() % 2;
	if (ucieczka)
	{
		int ruch = 0;
		while (!setPozycja({ getX() + poruszanie[ruch][0], getY() + poruszanie[ruch][1] }, true))
		{
			ruch++;

			if (ruch == 8)
			{
				swiat->dodajLog(this, " Nie udalo sie uciec :(");
				return false;

			}
		}

		swiat->dodajLog(this, " Udalo sie uciec :)");
		return true;
	}

	return false;

}

Antylopa* Antylopa::potomek()
{
	return new Antylopa(*this);

}