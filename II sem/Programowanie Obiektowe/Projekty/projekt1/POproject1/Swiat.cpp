#include <fstream>
#include <chrono>
#include <time.h>
#include <iomanip>
#include "Swiat.h"
#include "Organizm.h"
#include "Antylopa.h"
#include "Czlowiek.h"
#include "BarszczSosnowskiego.h"
#include "Guarana.h"
#include "Lis.h"
#include "Mlecz.h"
#include "Owca.h"
#include "Roslina.h"
#include "Trawa.h"
#include "WilczeJagody.h"
#include "Wilk.h"
#include "Zolw.h"
#include "Zwierze.h"

Organizm* Swiat::getOrganizm(pair < int, int > pozycja)
{
	if (pozycja.first < 0 || pozycja.first >= szerokosc || pozycja.second < 0 || pozycja.second >= wysokosc)
		return nullptr;

	for (Organizm* o : organizmy)
	{
		if (o->getX() == pozycja.first && o->getY() == pozycja.second)
			return o;

	}

	return nullptr;

}

void Swiat::dodajLog(Organizm* zrodlo, string l)
{
	string nazwa = typeid(*zrodlo).name();
	nazwa = zrodlo->getIkonka() + '(' + nazwa.substr(6, nazwa.length()) + ')';
	wpisyLogow++;

	cout << "\033[" << wysokosc + wpisyLogow + 4 << ";0H";
	cout << nazwa << l;
}

void Swiat::CzyscLogi()
{
	cout << "\x1B[2J";
	wpisyLogow = 0;
}

Organizm* Swiat::getCzlowiek()
{
	return czlowiek;
}

void Swiat::zapisStanu()
{
	ofstream in;
	string nazwa = "save" + to_string(rand()) + ".csv";
	in.open(nazwa);
	in << nrTury << ';' << szerokosc << ';' << wysokosc << "\n";

	for (Organizm* o : organizmy)
	{
		if (o->getSila() > -1)
			in << o->toString() << "\n";
	}

	in.close();

	time_t czas = time(NULL);
	tm czasLok;
	localtime_s(&czasLok, &czas);
	ofstream in_list;
	string czasCon = to_string(czasLok.tm_mday) + '.' + to_string(czasLok.tm_mon) + '.' + to_string(czasLok.tm_year + 1900) + "r. " + to_string(czasLok.tm_hour) + ":" + to_string(czasLok.tm_min);
	in_list.open("saves.csv", ios::app);
	in_list << czasCon << ';' << nazwa << "\n";
	in_list.close();
	dodajLog(czlowiek, "Stan gry zostal zapisany\n");

}

void Swiat::dodajOrganizm(Organizm* organizm)
{
	organizmy.push_back(organizm);
}

Swiat::Swiat(int szerokosc, int wysokosc)
{
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;
	czyNarysowany = false;
	wpisyLogow = 0;
	nrTury = 0;
	czlowiek = nullptr;

}

Swiat* Swiat::instance = nullptr;

Swiat* Swiat::getInstance()
{
	return instance;
}

Swiat* Swiat::getInstance(int szerokosc, int wysokosc)
{
	if (instance != nullptr)
		delete instance;

	instance = new Swiat(szerokosc, wysokosc);
	return instance;

}

Swiat* Swiat::getInstance(ifstream& in)
{
	delete instance;
	string linijka;
	int szerokosc, wysokosc, nrTury;

	getline(in, linijka, ';');
	nrTury = stoi(linijka);
	getline(in, linijka, ';');
	szerokosc = stoi(linijka);
	getline(in, linijka);
	wysokosc = stoi(linijka);
	instance = new Swiat(szerokosc, wysokosc);
	instance->nrTury = nrTury;

	while (getline(in, linijka, ';'))
	{
		Organizm* org = nullptr;

		if (linijka.size() < 2)
			continue;

		string nazwa = linijka.substr(linijka.find(' ') + 1, linijka.size());
		getline(in, linijka, ';');
		int x = stoi(linijka);
		getline(in, linijka, ';');
		int y = stoi(linijka);
		getline(in, linijka, ';');
		int sila = stoi(linijka);
		getline(in, linijka, ';');
		int wiek = stoi(linijka);

		if (nazwa == "Czlowiek")
		{
			org = new Czlowiek(x, y);
			instance->czlowiek = org;
			getline(in, linijka, ';');
			int umiejetnosc = stoi(linijka);
			((Czlowiek*)org)->setUm(umiejetnosc);

		}
		else if (nazwa == "Antylopa")
			org = new Antylopa(x, y);
		else if (nazwa == "BarszczSosnowskiego")
			org = new BarszczSosnowskiego(x, y);
		else if (nazwa == "Guarana")
			org = new Guarana(x, y);
		else if (nazwa == "Lis")
			org = new Lis(x, y);
		else if (nazwa == "Mlecz")
			org = new Mlecz(x, y);
		else if (nazwa == "Owca")
			org = new Owca(x, y);
		else if (nazwa == "Trawa")
			org = new Trawa(x, y);
		else if (nazwa == "WilczeJagody")
			org = new WilczeJagody(x, y);
		else if (nazwa == "Wilk")
			org = new Wilk(x, y);
		else if (nazwa == "Zolw")
			org = new Zolw(x, y);

		org->wzmacnianie(sila - org->getSila());
		org->postarz(wiek);
	}
	return instance;

}

void Swiat::poczPopulacja()
{
	czlowiek = new Czlowiek(rand() % szerokosc, rand() % wysokosc);
	new Antylopa(rand() % szerokosc, rand() % wysokosc);
	new BarszczSosnowskiego(rand() % szerokosc, rand() % wysokosc);
	new Guarana(rand() % szerokosc, rand() % wysokosc);
	new Lis(rand() % szerokosc, rand() % wysokosc);
	new Mlecz(rand() % szerokosc, rand() % wysokosc);
	new Owca(rand() % szerokosc, rand() % wysokosc);
	new Trawa(rand() % szerokosc, rand() % wysokosc);
	new WilczeJagody(rand() % szerokosc, rand() % wysokosc);
	new Wilk(rand() % szerokosc, rand() % wysokosc);
	new Zolw(rand() % szerokosc, rand() % wysokosc);

}

void Swiat::wykonajTure()
{
	CzyscLogi();
	nrTury++;
	organizmy.sort(Organizm::pierwszenstwo);

	for (Organizm* o : organizmy)
	{
		if (o->getSila() > -1)
			o->akcja();

		else break;

	}
}

void Swiat::rysowanieSwiata()
{

	cout << "\033[0;0H";
	for (int i = 0; i < szerokosc * 2 + 2; i++)
		cout << '#';

	cout << '\n';

	for (int i = 0; i < wysokosc; i++)
	{
		cout << '#';

		for (int j = 0; j < szerokosc * 2; j++)
			cout << ' ';

		cout << "#\n";

	}

	for (int i = 0; i < szerokosc * 2 + 2; i++)
		cout << '#';

	cout << '\n';

	for (Organizm* o : organizmy)
		if (o->getSila() > -1)
			o->rysuj();

	cout << "\033[" << wysokosc + 3 << ";0H";
	cout << "Tura " << nrTury << '\n';

}

int Swiat::getSzerokosc()
{
	return szerokosc;
}

int Swiat::getWysokosc()
{
	return wysokosc;

}