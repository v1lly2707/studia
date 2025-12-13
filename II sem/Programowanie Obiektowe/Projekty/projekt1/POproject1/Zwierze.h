#pragma once
#include "Organizm.h"

class Zwierze :
	public Organizm

{
public:

	Zwierze(string ikonka, int sila, int inicjatywa, int x, int y);
	virtual void akcja();
	virtual void kolizja(Organizm* inny);

};