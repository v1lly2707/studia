#include "Trawa.h"

Trawa::Trawa(int x, int y) : Roslina(EMOJI ? u8"T" : "Tr", 0, x, y)
{

}

Organizm* Trawa::potomek()
{
	return new Trawa(*this);
}