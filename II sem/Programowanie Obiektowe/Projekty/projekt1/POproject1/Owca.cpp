#include "Owca.h"

Owca::Owca(int x, int y) : Zwierze(EMOJI ? u8"O" : "Ow", 4, 4, x, y)
{

}

Owca* Owca::potomek()
{
	return new Owca(*this);
}