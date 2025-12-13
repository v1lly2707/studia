#include "Roslina.h"
#include "Swiat.h"

Roslina::Roslina(string ikonka, int sila, int x, int y) : Organizm(ikonka, sila, 0, x, y)
{

}

void Roslina::akcja()
{
	bool czyZasiane = rand() % 100 == 0;
	if (czyZasiane)
	{
		auto potomek = dynamic_cast < Roslina* > (this->potomek());
		int ruch = rand() % 4;

		while (!potomek->setPozycja({ getX() + poruszanie[ruch % 4][0],getY() + poruszanie[ruch % 4][1] }, true))
		{
			ruch++;
			
			if (ruch > 8)
			{
				swiat->dodajLog(this, " Brak miejsca na rozsianie");
				potomek->zabijanie();
				return;

			}
		}
		swiat->dodajLog(this, " Udalo sie rozsiac:)");

	}
}

void Roslina::kolizja(Organizm* inny)
{
	if (this == inny)
		return;

	if (getSila() > inny->getSila())
	{
		//cout << "ifdhehfe\n";
		swiat->dodajLog(this, " Wrog zostal otruty!");
		inny->zabijanie();

	}

	else if (getSila() < inny->getSila())
	{
		//cout << "hdiehd\n";
		swiat->dodajLog(this, " Roslina zostala zniszczona:(");
		zabijanie();
	}
	else if(getSila() == inny->getSila())
	{
		//cout << "diedije\n";
		swiat->dodajLog(this, " Remis!");
		
		zabijanie();

	}
}