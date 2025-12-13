#include "Swiat.h"
#include "Zolw.h"

Zolw::Zolw(int x, int y) : Zwierze(EMOJI ? u8"Z" : "Zo", 2, 1, x, y)
{

}

void Zolw::kolizja(Organizm* inny)
{
	if (inny->getSila() < 5 && typeid(*this) != typeid(*inny))
	{
		swiat->dodajLog(this, " Atak zakonczony niepowodzeniem :(");
		inny->cofnijRuch();
	}

	else Zwierze::kolizja(inny);
}

void Zolw::akcja()
{
	bool czyRuch = (rand() % 100) >= 75;
	if (czyRuch)
		Zwierze::akcja();
	else postarz();
}

Zolw* Zolw::potomek()
{
	return new Zolw(*this);
}