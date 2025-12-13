#pragma once
#include <algorithm>
#include <list>
#include "Organizm.h"

using namespace std;

class Swiat
{
private:

	list < Organizm* > organizmy;
	int szerokosc;
	int wysokosc;
	Organizm* czlowiek;
	bool czyNarysowany;

	int wpisyLogow;
	int nrTury;
	void CzyscLogi();

	Swiat(int szerokosc, int wysokosc);
	static Swiat* instance;

public:

	static Swiat* getInstance();
	static Swiat* getInstance(int szerokosc, int wysokosc);
	static Swiat* getInstance(ifstream& plik);
	void rysowanieSwiata();
	void wykonajTure();

	int getSzerokosc();
	int getWysokosc();

	void dodajLog(Organizm* zrodlo, string log);
	void poczPopulacja();
	Organizm* getOrganizm(pair < int, int > pozycja);
	void dodajOrganizm(Organizm* organizm);
	Organizm* getCzlowiek();
	void zapisStanu();

};