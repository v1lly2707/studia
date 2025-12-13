#include "Wilk.h"

Wilk::Wilk(int x, int y) : Zwierze(EMOJI ? u8"Wi" : "Wi", 9, 5, x, y)
{

}

Wilk* Wilk::potomek()
{
	return new Wilk(*this);
}