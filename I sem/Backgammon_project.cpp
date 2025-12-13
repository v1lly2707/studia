#include <ncurses/ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define MAX_ROZMIAR_STOSU 16
#define LICZBA_STOSOW 24

typedef struct {
	int wierzcholekStosu;
	int elementy[MAX_ROZMIAR_STOSU];
}
Stos;

typedef struct {
	int y;
	int x;
	char zawartosc[100];
	int uzytyKolor;
}
ElementyEkranu;

typedef struct {
	int colorPair;
	int yPos;
	const char* text;
} MenuItem;

MenuItem menuItems[] = {
	{3, 1, "====== MENU UZYTKOWNIKA ======"},
	{4, 2, "Filip Swiniarski  197725"},
	{4, 3, "Nacisnij (R) aby rozpoczac gre"},
	{3, 4, "=============================="},
	{1, 5, "Instrukcja sterowania programem:"},
	{1, 6, "- Uzyj klawiszy strzalek lewo/prawo do wyboru pola."},
	{1, 7, "- Nacisnij spacje, aby wybrac pole z ktorego przenosisz pion"},
	{1, 8, "  i docelowy dla pionka po ponownym nacisnieciu spacji."},
	{1, 9, "- Rzucenie kostkami odbywa sie automatycznie na poczatku tury."},
	{1, 10, "- Nacisnij klawisz 'z', aby zapisac stan gry."},
	{1, 11, "- Nacisnij klawisz 'w', aby wczytac stan gry."},
};

ElementyEkranu elementy[] = {
	{18, 63, "1", 0},   {18, 58, "2", 0},   {18, 53, "3", 0},   {18, 48, "4", 0},   {18, 43, "5", 0},   {18, 38, "6", 0},
	{18, 27, "7", 0},   {18, 22, "8", 0},   {18, 17, "9", 0},   {18, 12, "10", 0},  {18, 7, "11", 0},   {18, 2, "12", 0},
	{2, 2, "13", 0},    {2, 7, "14", 0},    {2, 12, "15", 0},   {2, 17, "16", 0},   {2, 22, "17", 0},   {2, 27, "18", 0},
	{2, 37, "19", 0},   {2, 42, "20", 0},   {2, 47, "21", 0},   {2, 52, "22", 0},   {2, 57, "23", 0},   {2, 62, "24", 0},
	{2, 32, "| |", 1},  {3, 32, "| |", 1},  {4, 32, "| |", 1},  {5, 32, "| |", 1},  {6, 32, "| |", 1},  {7, 32, "| |", 1},
	{8, 32, "| |", 1},  {9, 32, "| |", 1},  {10, 32, "| |", 1}, {11, 32, "| |", 1}, {12, 32, "| |", 1}, {13, 32, "| |", 1},
	{14, 32, "| |", 1}, {15, 32, "| |", 1}, {16, 32, "| |", 1}, {17, 32, "| |", 1}, {18, 32, "| |", 1}, {1, 2, "------------------------------------------------------------------", 0},
	{2, 1, "|", 0},     {3, 1, "|", 0},     {4, 1, "|", 0},     {5, 1, "|", 0},     {6, 1, "|", 0},     {7, 1, "|", 0},
	{8, 1, "|", 0},     {9, 1, "|", 0},     {10, 1, "|", 0},    {11, 1, "|", 0},    {12, 1, "|", 0},    {13, 1, "|", 0},
	{14, 1, "|", 0},    {15, 1, "|", 0},    {16, 1, "|", 0},    {17, 1, "|", 0},    {18, 1, "|", 0},    {18, 1, "|", 0},
	{2, 68, "|", 0},    {3, 68, "|", 0},    {4, 68, "|", 0},    {5, 68, "|", 0},    {6, 68, "|", 0},    {7, 68, "|", 0},
	{8, 68, "|", 0},    {9, 68, "|", 0},    {10, 68, "|", 0},   {11, 68, "|", 0},   {12, 68, "|", 0},   {13, 68, "|", 0},
	{14, 68, "|", 0},   {15, 68, "|", 0},   {16, 68, "|", 0},   {17, 68, "|", 0},   {18, 68, "|", 0},   {19, 2, "------------------------------------------------------------------", 0},
};

void inicjalizujStos(Stos* s)
{
	s->wierzcholekStosu = -1;
}

int czyStosPusty(Stos* s)
{
	return s->wierzcholekStosu == -1;
}

int rozmiarStosu(Stos* s)
{
	return s->wierzcholekStosu + 1;
}

int czyStosPelny(Stos* s)
{
	return s->wierzcholekStosu == MAX_ROZMIAR_STOSU - 1;
}

void wrzucNaStos(Stos* s, int element)
{
	if (czyStosPelny(s))
	{
		return;
	}

	s->elementy[++s->wierzcholekStosu] = element;
}

int zdejmijZeStosu(Stos* s)
{
	if (czyStosPusty(s))
	{
		return -1; // zwraca -1 jesli stos jest pusty
	}

	return s->elementy[s->wierzcholekStosu--]; // zdejmowanie elementu ze stosu
}

int pogladWierzcholkaStosu(Stos* s)
{
	if (czyStosPusty(s))
	{
		return -1;
	}

	return s->elementy[s->wierzcholekStosu];
}

char pobierzElementZeStosu(Stos* s, int indeks)
{
	if (indeks < 0 || indeks > s->wierzcholekStosu)
	{
		return '0';
	}

	return s->elementy[indeks];
}
//zmienianie pozycji
void przesunPozycjeGracza(int* wybranePole, int znakKlawiatury)
{
	switch (znakKlawiatury)
	{
	case KEY_LEFT:

		*
			wybranePole = *wybranePole + 1;

		if (*wybranePole >= 24) *wybranePole = 23;
		break;

	case KEY_RIGHT:

		*
			wybranePole = *wybranePole - 1;

		if (*wybranePole <= -1) *wybranePole = 0;
		break;
	}
}

int rzutKostka()
{
	return 1 + rand() % 6; // generowanie wartosci kostki
}

void zapiszStan(Stos stosy[], int gracz, int kostkaA, int kostkaB)
{
	FILE* plik = fopen("stan_gry.txt", "w");
	if (plik == NULL)
	{
		perror("Blad przy otwieraniu pliku");
		return;
	}

	fprintf(plik, "%d %d %d\n", gracz, kostkaA, kostkaB);

	for (int i = 0; i < LICZBA_STOSOW; i++)
	{
		fprintf(plik, "%d ", stosy[i].wierzcholekStosu);
		for (int j = 0; j <= stosy[i].wierzcholekStosu; j++)
		{
			fprintf(plik, "%d ", stosy[i].elementy[j]);
		}

		fprintf(plik, "\n");
	}

	fclose(plik);
}

bool wczytajStan(Stos stosy[], int* gracz, int* kostkaA, int* kostkaB)
{
	FILE* plik = fopen("stan_gry.txt", "r");
	if (plik == NULL)
	{
		perror("Blad przy otwieraniu pliku");
		return false;
	}

	fscanf(plik, "%d %d %d\n", gracz, kostkaA, kostkaB);

	for (int i = 0; i < LICZBA_STOSOW; i++)
	{
		fscanf(plik, "%d", &stosy[i].wierzcholekStosu);
		for (int j = 0; j <= stosy[i].wierzcholekStosu; j++)
		{
			fscanf(plik, "%d", &stosy[i].elementy[j]);
		}
	}

	fclose(plik);
	return true;
}

void aktualizujKolor(int i, int* wybranoPole, WINDOW* w,
	ElementyEkranu elementy[])
{
	if (*wybranoPole == i)
	{
		wattron(w, COLOR_PAIR(2));
		mvwprintw(w, elementy[i].y, elementy[i].x, "%s", elementy[i].zawartosc);
		wattroff(w, COLOR_PAIR(2));
	}
	else
	{
		mvwprintw(w, elementy[i].y, elementy[i].x, "%s", elementy[i].zawartosc);
	}

	if (i > 24 + 16)
	{
		wattron(w, COLOR_PAIR(3));
		mvwprintw(w, elementy[i].y, elementy[i].x, "%s", elementy[i].zawartosc);
		wattroff(w, COLOR_PAIR(3));
	}
}

void aktualizujPozycje(int i, int wybranaPoz[], WINDOW* w,
	ElementyEkranu elementy[])
{
	if (wybranaPoz[0] == i)
	{
		wattron(w, COLOR_PAIR(4));
		mvwprintw(w, elementy[i].y, elementy[i].x, "%s", elementy[i].zawartosc);
		wattroff(w, COLOR_PAIR(4));
	}
}

void wyswietlElementy(int wybranaPoz[], int* wybranoPole, WINDOW* w,
	ElementyEkranu elementy[], int liczbaElementow)
{
	for (int i = 0; i < liczbaElementow; i++)
	{
		aktualizujKolor(i, wybranoPole, w, elementy);
		if (i >= 24 && i < 24 + 17)
		{
			wattron(w, COLOR_PAIR(1));
			mvwprintw(w, elementy[i].y, elementy[i].x, "%s",
				elementy[i].zawartosc);
			wattroff(w, COLOR_PAIR(1));
		}

		aktualizujPozycje(i, wybranaPoz, w, elementy);
	}
}

void wyswietlPlansze(ElementyEkranu elementy[], int pozycja[], int* pole,
	WINDOW* w)
{
	int liczbaElementow = 78;

	wyswietlElementy(pozycja, pole, w, elementy, liczbaElementow);
}

bool czyRuchJestPrawidlowy_(int odleglosc, int obecnieGrajacy, int kostkaA,
	int kostkaB, bool czyKostkaAUzyta,
	bool czyKostkaBUzyta)
{
	if (obecnieGrajacy == 1)
		return ((odleglosc == kostkaA && !czyKostkaAUzyta) ||
			(odleglosc == kostkaB && !czyKostkaBUzyta) ||
			(odleglosc == kostkaA + kostkaB && !czyKostkaAUzyta &&
				!czyKostkaBUzyta));
	else
		return ((-odleglosc == kostkaA && !czyKostkaAUzyta) ||
			(-odleglosc == kostkaB && !czyKostkaBUzyta) ||
			(-odleglosc == kostkaA + kostkaB && !czyKostkaAUzyta &&
				!czyKostkaBUzyta));
	return false;
}

void obsluzBicie(Stos stosy[], int dokad, int obecnieGrajacy)
{
	if (rozmiarStosu(&stosy[dokad]) == 1 &&
		pogladWierzcholkaStosu(&stosy[dokad]) != obecnieGrajacy)
	{
		zdejmijZeStosu(&stosy[dokad]);
	}
}

void aktualizujUzycieKosci(int odleglosc, int kostkaA, int kostkaB,
	bool& czyKostkaAUzyta, bool& czyKostkaBUzyta)
{
	if (odleglosc == kostkaA || -odleglosc == kostkaA)
	{
		czyKostkaAUzyta = true;
	}

	if (odleglosc == kostkaB || -odleglosc == kostkaB)
	{
		czyKostkaBUzyta = true;
	}

	if (odleglosc == kostkaA + kostkaB || -odleglosc == kostkaA + kostkaB)
	{
		czyKostkaAUzyta = true;
		czyKostkaBUzyta = true;
	}
}

void przeniesPionek(Stos stosy[], int skad, int dokad)
{
	int gracz = zdejmijZeStosu(&stosy[skad]);
	wrzucNaStos(&stosy[dokad], gracz);
}

bool przesunPionek(Stos stosy[], int skad, int dokad, int& obecnieGrajacy,
	int kostkaA, int kostkaB, bool& czyKostkaAUzyta,
	bool& czyKostkaBUzyta)
{
	int odleglosc = dokad - skad;

	if ((!czyRuchJestPrawidlowy_(odleglosc, obecnieGrajacy, kostkaA, kostkaB,
		czyKostkaAUzyta, czyKostkaBUzyta) ||
		skad < 0 || skad >= LICZBA_STOSOW || dokad < 0 ||
		dokad >= LICZBA_STOSOW) ||
		(rozmiarStosu(&stosy[dokad]) > 1 &&
			(pogladWierzcholkaStosu(&stosy[dokad]) != obecnieGrajacy)))
		return false;

	obsluzBicie(stosy, dokad, obecnieGrajacy);
	przeniesPionek(stosy, skad, dokad);
	aktualizujUzycieKosci(odleglosc, kostkaA, kostkaB, czyKostkaAUzyta, czyKostkaBUzyta);
	return true;
}

void ustawPoczatkowePionki(Stos stosy[])
{
	int dane[][3] = {
		{ 0, 2, 1 },
		{ 5, 5, 2 },
		{ 7, 3, 2 },
		{ 11, 5, 1 },
		{ 12, 5, 2 },
		{ 16, 3, 1 },
		{ 18, 5, 1 },
		{ 23, 2, 2 }
	};

	for (int i = 0; i < sizeof(dane) / sizeof(dane[0]); i++)
	{
		for (int j = 0; j < dane[i][1]; j++)
		{
			wrzucNaStos(&stosy[dane[i][0]], dane[i][2]);
		}
	}
}

void konfigurujUI(WINDOW** w)
{
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	noecho();
	curs_set(0);
	*w = newwin(23, 80, 4, 3);
	keypad(*w, TRUE);
	wtimeout(*w, 0);
}

void wyswietlMenuUzytkownika(WINDOW* w)
{
	for (int i = 0; i < sizeof(menuItems) / sizeof(menuItems[0]); i++)
	{
		if (menuItems[i].yPos < 6)
			wattron(w, COLOR_PAIR(menuItems[i].colorPair));
		mvwprintw(w, menuItems[i].yPos, 1, "%s", menuItems[i].text);
		if (menuItems[i].yPos < 6)
			wattroff(w, COLOR_PAIR(menuItems[i].colorPair));
	}
}

bool obsluzMenu(WINDOW* w, int klawiatura)
{
	wyswietlMenuUzytkownika(w);
	if ((klawiatura & A_CHARTEXT) == 'r')
	{
		return false;
	}

	return true;
}

void zmienGraczaRzucKostki(int* graczID, bool* czyKostkaAUzyta,
	bool* czyKostkaBUzyta, int* kostkaA, int* kostkaB)
{
	*graczID = (*graczID == 1) ? 2 : 1;
	*czyKostkaAUzyta = false;
	*czyKostkaBUzyta = false;
	*kostkaA = rzutKostka();
	*kostkaB = rzutKostka();
}

void zresetujWybory2(int pozycjePrzenoszeniaPionkow[], int* wybranePole)
{
	*wybranePole = 0;
	pozycjePrzenoszeniaPionkow[0] = -1;
	pozycjePrzenoszeniaPionkow[1] = -1;
}

void zresetujWybory(int pozycjePrzenoszeniaPionkow[])
{
	pozycjePrzenoszeniaPionkow[0] = -1;
	pozycjePrzenoszeniaPionkow[1] = -1;
}

void inicjalizujStosy(Stos stosy[])
{
	for (int i = 0; i < LICZBA_STOSOW; i++) inicjalizujStos(&stosy[i]);
}

void inicjalizujLosowosc()
{
	srand(time(NULL));
}

void inicjalizujGre(ElementyEkranu elementy[], int pozycjePrzenoszeniaPionkow[],
	int* wybranePole, Stos stosy[])
{
	inicjalizujLosowosc();
	zresetujWybory2(pozycjePrzenoszeniaPionkow, wybranePole);
	inicjalizujStosy(stosy);
	ustawPoczatkowePionki(stosy);
}

void obslugaZapisuWczytywania(int klawiatura, Stos stosy[], int graczID,
	int kostkaA, int kostkaB)
{
	if ((klawiatura & A_CHARTEXT) == 'z')
	{
		zapiszStan(stosy, graczID, kostkaA, kostkaB);
	}

	if ((klawiatura & A_CHARTEXT) == 'w')
	{
		wczytajStan(stosy, &graczID, &kostkaA, &kostkaB);
	}
}

void rozpocznijGre(ElementyEkranu elementy[], int pozycjePrzenoszeniaPionkow[],
	int* wybranePole, Stos stosy[], WINDOW** w, int* kostkaA,
	int* kostkaB)
{
	inicjalizujGre(elementy, pozycjePrzenoszeniaPionkow, wybranePole, stosy);
	konfigurujUI(w);
	*kostkaA = rzutKostka();
	*kostkaB = rzutKostka();
}

void obsluzRuchGracza(Stos stosy[], int pozycjePrzenoszeniaPionkow[], int* nrPozycjiZapisanej, int* wybranePole, int* graczID, int* kostkaA, int* kostkaB, bool* czyKostkaAUzyta, bool* czyKostkaBUzyta)
{
	pozycjePrzenoszeniaPionkow[*nrPozycjiZapisanej] = *wybranePole;
	(*nrPozycjiZapisanej)++;

	if (*nrPozycjiZapisanej == 2)
	{
		*nrPozycjiZapisanej = 0;

		if (przesunPionek(stosy, pozycjePrzenoszeniaPionkow[0],
			pozycjePrzenoszeniaPionkow[1], *graczID,
			*kostkaA, *kostkaB, *czyKostkaAUzyta,
			*czyKostkaBUzyta))
		{
			if (*czyKostkaAUzyta && *czyKostkaBUzyta)
			{
				zmienGraczaRzucKostki(graczID, czyKostkaAUzyta, czyKostkaBUzyta, kostkaA, kostkaB);
			}

			zresetujWybory(pozycjePrzenoszeniaPionkow);
		}
		else
		{
			zresetujWybory(pozycjePrzenoszeniaPionkow);
		}
	}
}

void rysujPionek(WINDOW* w, int i, int j, int dx, char znak)
{
	int x, y;
	if (i < 6)
		x = 7 + 5 * (11 - i), y = 17 - j;
	else if (i < 12)
		x = 7 + 5 * (10 - i) - 1, y = 17 - j;
	else if (i < 18)
		x = 1 + dx, y = 3 + j;
	else
		x = 1 + dx + 6, y = 3 + j;

	mvwprintw(w, y, x, " %c", znak);
}

void rysujPionki(WINDOW* w, Stos stosy[])
{
	int dx = 0;

	for (int i = 0; i < LICZBA_STOSOW; i++)
	{
		for (int j = 0; j < rozmiarStosu(&stosy[i]); j++)
		{
			char znak = pobierzElementZeStosu(&stosy[i], j) == 1 ? 'O' : 'X';
			rysujPionek(w, i, j, dx, znak);
		}

		if (i >= 12) dx = dx + 5;
	}
}

void aktualizujUI(WINDOW* w, int graczID, int kostkaA, int kostkaB, Stos stosy[], ElementyEkranu elementy[], int pozycjePrzenoszeniaPionkow[], int wybranePole)
{
	werase(w);
	mvwprintw(w, 21, 1, "Wypadlo: %d, %d", kostkaA, kostkaB);

	if (graczID == 2)
		mvwprintw(w, 22, 1, "Kolej gracza X");
	else if (graczID == 1)
		mvwprintw(w, 22, 1, "Kolej gracza O");

	rysujPionki(w, stosy);

	mvwprintw(w, 20, 1,
		"Aby zapisac rozgrywke wcisnij 'z', w celu wczytania 'w'");
	wyswietlPlansze(elementy, pozycjePrzenoszeniaPionkow, &wybranePole,
		w);
}

void przetwarzajWejscie(int klawiatura, Stos stosy[], int pozycjePrzenoszeniaPionkow[], int* nrPozycjiZapisanej, int* wybranePole, int* graczID, int* kostkaA, int* kostkaB, bool* czyKostkaAUzyta, bool* czyKostkaBUzyta)
{
	if ((klawiatura & A_CHARTEXT) == ' ')
	{
		obsluzRuchGracza(stosy, pozycjePrzenoszeniaPionkow, nrPozycjiZapisanej, wybranePole, graczID, kostkaA, kostkaB, czyKostkaAUzyta, czyKostkaBUzyta);
	}
}

void wykonajLogikeGry(WINDOW* w, Stos stosy[], ElementyEkranu elementy[], int pozycjePrzenoszeniaPionkow[], int& nrPozycjiZapisanej, int& wybranePole, int& graczID, int& kostkaA, int& kostkaB, bool& czyKostkaAUzyta, bool& czyKostkaBUzyta, int klawiatura)
{
	przetwarzajWejscie(klawiatura, stosy, pozycjePrzenoszeniaPionkow, &nrPozycjiZapisanej, &wybranePole, &graczID, &kostkaA, &kostkaB, &czyKostkaAUzyta, &czyKostkaBUzyta);

	przesunPozycjeGracza(&wybranePole, klawiatura);

	aktualizujUI(w, graczID, kostkaA, kostkaB, stosy, elementy, pozycjePrzenoszeniaPionkow, wybranePole);

	obslugaZapisuWczytywania(klawiatura, stosy, graczID, kostkaA,
		kostkaB);

}

void zakonczTure(WINDOW* w)
{
	wrefresh(w);
	napms(16);	// Odczekaj
}

void petlaGry(WINDOW* w, Stos stosy[], ElementyEkranu elementy[], int pozycjePrzenoszeniaPionkow[], int& kostkaA, int& kostkaB, bool& czyKostkaAUzyta, bool& czyKostkaBUzyta)
{
	int wybranePole = 0, nrPozycjiZapisanej = 0, graczID = 2;
	bool czyMenuJestWlaczone = true;
	for (;;)
	{
		int klawiatura = wgetch(w);

		if (czyMenuJestWlaczone)
		{
			czyMenuJestWlaczone = obsluzMenu(w, klawiatura);
			wrefresh(w);
		}
		else
		{
			wykonajLogikeGry(w, stosy, elementy, pozycjePrzenoszeniaPionkow, nrPozycjiZapisanej, wybranePole, graczID, kostkaA, kostkaB, czyKostkaAUzyta, czyKostkaBUzyta, klawiatura);
		}

		zakonczTure(w);
	}
}

int main(void)
{
	inicjalizujLosowosc();

	int pozycjePrzenoszeniaPionkow[2] = { -1, -1 };

	int wybranePole = 0, kostkaA, kostkaB;
	bool czyKostkaAUzyta = false, czyKostkaBUzyta = false;
	Stos stosy[LICZBA_STOSOW];
	WINDOW* w;

	rozpocznijGre(elementy, pozycjePrzenoszeniaPionkow, &wybranePole, stosy, &w, &kostkaA, &kostkaB);

	petlaGry(w, stosy, elementy, pozycjePrzenoszeniaPionkow, kostkaA, kostkaB, czyKostkaAUzyta, czyKostkaBUzyta);

}
