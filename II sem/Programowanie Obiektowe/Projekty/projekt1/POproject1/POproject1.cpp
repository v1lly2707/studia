#include <fstream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <chrono>
#include "Swiat.h"
#include "Czlowiek.h"

using namespace std;

enum opcje
{
	lewo = 75,
	prawo = 77,
	gora = 72,
	dol = 80,
	enter = 13,
	zapis = 's',
	wczytywanie = 'l',
	umiejetnosc = 'u',
	pomoc = 'h',
	wyjscie = 'q'


};

int main()
{
	srand(time(NULL));
	ios::sync_with_stdio(0);
	int wysokosc, szerokosc,numer;
	char opcja;
	string linijka;
	ifstream lista_plikow;
	ifstream plik;

	SetConsoleTitle(L"Filip Świniarski idx 197725");
	SetConsoleOutputCP(CP_UTF8);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 15;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Courier New");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	cout << "Podaj szerokosc swiata:\n";
	cin >> szerokosc;
	cout << "Podaj wysokosc swiata:\n";
	cin >> wysokosc;
	cout << "\n";

	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	Swiat* swiat = Swiat::getInstance(szerokosc, wysokosc);
	swiat->poczPopulacja();
	cout << "\n\n\n";
	cout << "\x1B[2J\033[0;0H";
	swiat->rysowanieSwiata();


	while (1)
	{
		Czlowiek* czlowiek = dynamic_cast <Czlowiek*> (swiat->getCzlowiek());
		opcja = _getch();
		

		if (czlowiek != nullptr)
			switch (opcja)
			{
			case lewo:
				if (!czlowiek->setXY({ -1,0 }))
					continue;

				break;
			
			case prawo:
				if (!czlowiek->setXY({ 1,0 }))
					continue;

				break;

			case gora:
				if (!czlowiek->setXY({ 0,-1 }))
					continue;

				break;

			case dol:
				if (!czlowiek->setXY({ 0,1 }))
					continue;

				break;

			case umiejetnosc:
				czlowiek->aktywujUm();
				continue;

			case enter:
				break;

			case pomoc:
				cout << "\x1B[2J\033[0;0H";
				cout << "Poruszanie sie czlowiekiem -> strzalki\n";
				cout << "Aktywacja umiejetnosci -> u\n";
				cout << "Nastepna tura -> enter\n";
				cout << "Wczytywanie z pliku -> l\n";
				cout << "Zapis do pliku -> s\n";
				cout << "Pomoc -> h\n";
				cout << "Wyjscie z gry -> q\n";

				break;

			case wyjscie:
				exit(0);
				break;

			case zapis:
				swiat->zapisStanu();
				continue;


			case wczytywanie:
				cout << "\x1B[2J\033[0;0H";
				lista_plikow.open("saves.csv");
				while (getline(lista_plikow, linijka, ';'))
				{
					cout << linijka << '-';
					getline(lista_plikow, linijka);
					cout << linijka << '\n';
				}

				cout << "Podaj nr pliku, ktory ma byc wczytany\n";
				cin >> numer;
				plik = ifstream("save" + to_string(numer) + ".csv");

				if (plik.is_open())
					swiat = Swiat::getInstance(plik);

				cout << "\x1B[2J\033[0;0H";
				swiat->rysowanieSwiata();
				plik.close();
				lista_plikow.close();

				continue;

			default:
				continue;




			}

			if (opcja != enter)
				continue;


			swiat->wykonajTure();
			swiat->rysowanieSwiata();
		
	}



	return 0;

}