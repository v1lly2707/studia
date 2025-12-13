#include "Swiat.h"
#include "Organizm.h"

Organizm::Organizm(string ikonka, int sila, int inicjatywa, int x, int y) {
	this->swiat = Swiat::getInstance();
	this->ikonka = ikonka;
	this->sila = sila;
	this->inicjatywa = inicjatywa;
	this->pozycja = { x, y };
	this->wiek = 0;
	swiat->dodajOrganizm(this);
}

Organizm::Organizm(const Organizm& a)
{
	this->swiat = a.swiat;
	this->ikonka = a.ikonka;
	this->sila = a.sila;
	this->inicjatywa = a.inicjatywa;
	this->pozycja = a.pozycja;
	this->wiek = 0;
	swiat->dodajOrganizm(this);
}



bool Organizm::uciekanie()
{
	return false;
}

string Organizm::toString()
{
	string out = "";
	out += typeid(*this).name();
	out += ";";
	out += to_string(pozycja.first);
	out += ";";
	out += to_string(pozycja.second);
	out += ";";
	out += to_string(sila);
	out += ";";
	out += to_string(wiek);
	out += ";";
	return out;
}

void Organizm::rysuj()
{
	cout << "\033[" << pozycja.second + 2 << ";" << pozycja.first * 2 + 2 << "H";
	cout << ikonka;
}

int Organizm::getSila()
{
	return sila;
}

int Organizm::getInicjatywa()
{
	return inicjatywa;
}

int Organizm::getWiek()
{
	return wiek;
}

string Organizm::getIkonka()
{
	return ikonka;
}

void Organizm::postarz(int wartosc)
{
	wiek += wartosc;
}

void Organizm::zabijanie()
{
	pozycja = { -1, -1 };
	sila = -1;
	inicjatywa = -1;
}

void Organizm::wzmacnianie(int wartosc)
{
	sila += wartosc;
}

int Organizm::getX()
{
	return pozycja.first;
}

int Organizm::getY()
{
	return pozycja.second;
}

bool Organizm::setPozycja(pair<int, int> pozycja, bool musiBycPuste)
{
	if (pozycja.first < 0 || pozycja.first >= swiat->getSzerokosc() || pozycja.second < 0 || pozycja.second >= swiat->getWysokosc())
		return false;
	if (musiBycPuste && swiat->getOrganizm(pozycja) != nullptr)
		return false;
	PoprzedniaPozycja = this->pozycja;
	Organizm* inny = swiat->getOrganizm(pozycja);
	this->pozycja = pozycja;
	swiat->dodajLog(this, " Ruch (" + to_string(PoprzedniaPozycja.first) + "," + to_string(PoprzedniaPozycja.second) + ") -> (" + to_string(pozycja.first) + "," + to_string(pozycja.second) + ")");
	if (inny != nullptr)
	{
		inny->kolizja(this);
	}
	return true;
}

void Organizm::cofnijRuch()
{
	setPozycja(PoprzedniaPozycja, false);
}

int Organizm::pierwszenstwo(Organizm* a, Organizm* b)
{
	if (a->inicjatywa > b->inicjatywa)
		return 1;
	else if (a->inicjatywa < b->inicjatywa)
		return 0;
	else
	{
		if (a->wiek > b->wiek)
			return 1;
		else
			return 0;
	}
}