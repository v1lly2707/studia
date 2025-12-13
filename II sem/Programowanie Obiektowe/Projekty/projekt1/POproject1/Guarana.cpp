#include "Swiat.h"
#include "Guarana.h"

Guarana::Guarana(int x, int y) : Roslina(EMOJI ? u8"Gu" : "Gu", 0, x, y)
{

}

void Guarana::kolizja(Organizm* inny)
{
	string nazwa = typeid(*inny).name();
	swiat->dodajLog(this, " Wzmocniono " + nazwa.substr(6));
	zabijanie();
	inny->wzmacnianie(3);
}


Organizm* Guarana::potomek()
{
	return new Guarana(*this);
}

