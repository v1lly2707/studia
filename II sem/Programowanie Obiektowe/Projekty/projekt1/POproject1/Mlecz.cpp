#include "Mlecz.h"

Mlecz::Mlecz(int x, int y) : Roslina(EMOJI ? u8"Ml" : "Ml", 0, x, y)
{

}

void Mlecz::akcja()
{
	for (int i = 0; i < 3; i++)
		Roslina::akcja();
}

Organizm* Mlecz::potomek()
{
	return new Mlecz(*this);
}
