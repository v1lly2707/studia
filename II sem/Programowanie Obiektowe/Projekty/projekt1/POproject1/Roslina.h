#pragma once
#include "Organizm.h"

class Roslina :
	public Organizm
{
public:

	Roslina(string ikonka, int sila, int x, int y);
	virtual void akcja();
	virtual void kolizja(Organizm* inny);

};