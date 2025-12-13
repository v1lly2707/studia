#pragma once
#include <iostream>
#include <string>
#define EMOJI 1

using namespace std;

class Swiat;

class Organizm
{
	int wiek;
	int sila;
	int inicjatywa;
	pair < int, int > pozycja;
	pair < int, int > PoprzedniaPozycja;
	string ikonka;


protected:

	Swiat* swiat;
	const int poruszanie[4][2] =
	{
		{0,1},
		{1,0},
		{0,-1},
		{-1,0}
	};

public:

	Organizm(string ikonka, int sila, int inicjatywa, int x, int y);
	Organizm(const Organizm& a);
	virtual void akcja() = 0;
	virtual void kolizja(Organizm* inny) = 0;
	virtual Organizm* potomek() = 0;
	virtual bool uciekanie();
	void rysuj();
	int getSila();
	int getWiek();
	int getInicjatywa();
	string getIkonka();
	virtual string toString();
	virtual void zabijanie();
	void wzmacnianie(int wartosc);
	void postarz(int wartosc = 1);


	int getX();
	int getY();
	bool setPozycja(pair < int, int > pozycja, bool czyPuste);
	void cofnijRuch();
	static int pierwszenstwo(Organizm* a, Organizm* b);


};