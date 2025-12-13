#include "Swiat.h"
#include "WilczeJagody.h"

WilczeJagody::WilczeJagody(int x, int y) : Roslina(EMOJI ? u8"WJ" : "WJ", 99, x, y)
{

}

void WilczeJagody::kolizja(Organizm* inny)
{
	string nazwa = typeid(*inny).name();
	swiat->dodajLog(this, " Wilcze jagody zatruly " + nazwa.substr(6));
	zabijanie();
	inny->zabijanie();

}

Organizm* WilczeJagody::potomek()
{
	return new WilczeJagody(*this);
}