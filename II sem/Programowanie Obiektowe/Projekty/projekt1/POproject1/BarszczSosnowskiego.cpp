#include "BarszczSosnowskiego.h"
#include "Zwierze.h"
#include "Swiat.h"


BarszczSosnowskiego::BarszczSosnowskiego(int x, int y) : Roslina(EMOJI ? u8"BS" : "BS", 10, x, y)
{

}

void BarszczSosnowskiego::akcja()
{
	for (int i = 0; i < 4; i++)
	{
		auto obok = swiat->getOrganizm({ getX() + poruszanie[i][0],getY() + poruszanie[i][1] });
		
		if (obok != nullptr)
		{
			bool czyZwierze = dynamic_cast<Zwierze*>(obok);

			if (czyZwierze)
			{
				swiat->dodajLog(this, " Otrucie:(");
				obok->zabijanie();
			}
		}
	}
}

void BarszczSosnowskiego::kolizja(Organizm* inny)
{
	string nazwa = typeid(*inny).name();
	swiat->dodajLog(this, " Zatrul " + nazwa.substr(6));
	inny->zabijanie();
	zabijanie();
}

Organizm* BarszczSosnowskiego::potomek()
{
	return new BarszczSosnowskiego(*this);
}