#include "Swiat.h"
#include "Zwierze.h"
#include "Lis.h"

Lis::Lis(int x, int y) : Zwierze(EMOJI ? u8"Li" : "Li", 3, 7, x, y)
{

}

void Lis::akcja()
{
	postarz();
	int ruch = rand() % 4;
	pair<int, int> nPoz;
	while (ruch <= 8) {
		nPoz = { getX() + poruszanie[ruch % 4][0], getY() + poruszanie[ruch % 4][1] };
		if (swiat->getOrganizm(nPoz) == nullptr) {
			if (setPozycja(nPoz, false))
				break;
		}
		else if (swiat->getOrganizm(nPoz)->getSila() <= getSila())
			if (setPozycja(nPoz, false))
				break;
		ruch++;
	}
}
Lis* Lis::potomek()
{
	return new Lis(*this);
}