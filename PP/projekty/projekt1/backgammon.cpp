#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <ctime>
#include <stdbool.h>
#include <stdio.h>
#define MAX_ROZMIAR_STOSU 16 
#define LICZBA_STOSOW 24    

typedef struct
{
    int wierzcholekStosu;           
    int elementy[MAX_ROZMIAR_STOSU];
} Stos;

typedef struct
{
    int y;               
    int x;               
    char zawartosc[100]; 
    int uzytyKolor;      // jaki kolor zostal uzyty
} ElementyEkranu;

void inicjalizujStos(Stos *s)
{
    s->wierzcholekStosu = -1; 
}

int czyStosPusty(Stos *s)
{
    return s->wierzcholekStosu == -1; 
}

int rozmiarStosu(Stos *s)
{
    return s->wierzcholekStosu + 1; 
}

int czyStosPelny(Stos *s)
{
    return s->wierzcholekStosu == MAX_ROZMIAR_STOSU - 1; 
}

void wrzucNaStos(Stos *s, int element)
{
    if (czyStosPelny(s))
    {
        return; 
    }
    s->elementy[++s->wierzcholekStosu] = element; 
}

int zdejmijZeStosu(Stos *s)
{
    if (czyStosPusty(s))
    {
        return -1; // zwraca -1, jesli stos jest pusty
    }
    return s->elementy[s->wierzcholekStosu--]; // zdejmowanie elementu ze stosu
}
int pogladWierzcholkaStosu(Stos *s)
{
    if (czyStosPusty(s))
    {
        return -1; // zwraca -1,jesli stos jest pusty
    }
    return s->elementy[s->wierzcholekStosu]; 
}

char pobierzElementZeStosu(Stos *s, int indeks)
{
    if (indeks < 0 || indeks > s->wierzcholekStosu)
    {
        return '0'; 
    }
    return s->elementy[indeks]; 
}

//zmienianei pozycji
void przesunPozycjeGracza(int *wybranePole, int znakKlawiatury)
{
    // strzalki do porusznai sie
    switch (znakKlawiatury)
    {
    // 
    case KEY_LEFT:
        
        *wybranePole = *wybranePole + 1;

        //ograniczenie poruszania sie
        if (*wybranePole >= 24)
            *wybranePole = 23;
        break;

    
    case KEY_RIGHT:
        
        *wybranePole = *wybranePole - 1;

       
        if (*wybranePole <= -1)
            *wybranePole = 0;
        break;
    }
}

int rzutKostka()
{
    return 1 + rand() % 6; //generowanie wartosci kostki
}

void zapiszStan(Stos stosy[], int gracz, int kostkaA, int kostkaB)
{
    FILE *plik = fopen("stan_gry.txt", "w");
    if (plik == NULL)
    {
        perror("bÄ¹â??A?â?¦d przy otwieraniu pliku");
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

bool wczytajStan(Stos stosy[], int *gracz, int *kostkaA, int *kostkaB)
{
    FILE *plik = fopen("stan_gry.txt", "r");
    if (plik == NULL)
    {
        perror("bÄ¹â??A?â?¦d przy otwieraniu pliku");
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

//wyswietlanie interfejsu
void wyswietlElementy(int wybranaPoz[], int *wybranoPole, WINDOW *w, ElementyEkranu elementy[], int liczbaElementow)
{
    
    for (int i = 0; i < liczbaElementow; i++)
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
        
        if (i >= 24 && i < 24 + 17)
        {
            wattron(w, COLOR_PAIR(1));
            mvwprintw(w, elementy[i].y, elementy[i].x, "%s", elementy[i].zawartosc);
            wattroff(w, COLOR_PAIR(1));
        }
        if (i > 24 + 16)
        {
            wattron(w, COLOR_PAIR(3));
            mvwprintw(w, elementy[i].y, elementy[i].x, "%s", elementy[i].zawartosc);
            wattroff(w, COLOR_PAIR(3));
        }

        
        if (wybranaPoz[0] == i)
        {
            wattron(w, COLOR_PAIR(4));

            mvwprintw(w, elementy[i].y, elementy[i].x, "%s", elementy[i].zawartosc);

            wattroff(w, COLOR_PAIR(4));
        }
    }
}

//wyswietlanie
void wyswietlPlansze(ElementyEkranu elementy[], int pozycja[], int *pole, WINDOW *w)
{
    
    int liczbaElementow = 78;

    
    wyswietlElementy(pozycja, pole, w, elementy, liczbaElementow);
}
//przesuwanie
bool przesunPionek(Stos stosy[], int skad, int dokad, int &obecnieGrajacy, int kostkaA, int kostkaB, bool &czyKostkaAUzyta, bool &czyKostkaBUzyta)
{
    
    int odleglosc = dokad - skad;
    bool czyRuchPrawidlowy = false;

    //sprawdzenie prawidlowosci ruchu
    if (obecnieGrajacy == 1)
    {
        czyRuchPrawidlowy = ((odleglosc == kostkaA && !czyKostkaAUzyta) ||
                             (odleglosc == kostkaB && !czyKostkaBUzyta) ||
                             (odleglosc == kostkaA + kostkaB && !czyKostkaAUzyta && !czyKostkaBUzyta));
    }
    else 
    {
        czyRuchPrawidlowy = ((-odleglosc == kostkaA && !czyKostkaAUzyta) ||
                             (-odleglosc == kostkaB && !czyKostkaBUzyta) ||
                             (-odleglosc == kostkaA + kostkaB && !czyKostkaAUzyta && !czyKostkaBUzyta));
    }

    
    if (!czyRuchPrawidlowy || skad < 0 || skad >= LICZBA_STOSOW || dokad < 0 || dokad >= LICZBA_STOSOW)
    {
        return false;
    }

    
    if (rozmiarStosu(&stosy[dokad]) > 1 && (pogladWierzcholkaStosu(&stosy[dokad]) != obecnieGrajacy))
    {
        return false;
    }

    
    if (rozmiarStosu(&stosy[dokad]) == 1 && pogladWierzcholkaStosu(&stosy[dokad]) != obecnieGrajacy)
    {
        zdejmijZeStosu(&stosy[dokad]);
    }

    
    int gracz = zdejmijZeStosu(&stosy[skad]);
    wrzucNaStos(&stosy[dokad], gracz);

    
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

    return true; 
}

int main(void)
{

 
    ElementyEkranu elementy[] = {
        {18, 63, "1", 0},
        {18, 58, "2", 0},
        {18, 53, "3", 0},
        {18, 48, "4", 0},
        {18, 43, "5", 0},
        {18, 38, "6", 0},
        {18, 27, "7", 0},
        {18, 22, "8", 0},
        {18, 17, "9", 0},
        {18, 12, "10", 0},
        {18, 7, "11", 0},
        {18, 2, "12", 0},
        {2, 2, "13", 0},
        {2, 7, "14", 0},
        {2, 12, "15", 0},
        {2, 17, "16", 0},
        {2, 22, "17", 0},
        {2, 27, "18", 0},
        {2, 37, "19", 0},
        {2, 42, "20", 0},
        {2, 47, "21", 0},
        {2, 52, "22", 0},
        {2, 57, "23", 0},
        {2, 62, "24", 0},
        {2, 32, "| |", 1},
        {3, 32, "| |", 1},
        {4, 32, "| |", 1},
        {5, 32, "| |", 1},
        {6, 32, "| |", 1},
        {7, 32, "| |", 1},
        {8, 32, "| |", 1},
        {9, 32, "| |", 1},
        {10, 32, "| |", 1},
        {11, 32, "| |", 1},
        {12, 32, "| |", 1},
        {13, 32, "| |", 1},
        {14, 32, "| |", 1},
        {15, 32, "| |", 1},
        {16, 32, "| |", 1},
        {17, 32, "| |", 1},
        {18, 32, "| |", 1},
        {1, 2, "------------------------------------------------------------------", 0},
        {2, 1, "|", 0},
        {3, 1, "|", 0},
        {4, 1, "|", 0},
        {5, 1, "|", 0},
        {6, 1, "|", 0},
        {7, 1, "|", 0},
        {8, 1, "|", 0},
        {9, 1, "|", 0},
        {10, 1, "|", 0},
        {11, 1, "|", 0},
        {12, 1, "|", 0},
        {13, 1, "|", 0},
        {14, 1, "|", 0},
        {15, 1, "|", 0},
        {16, 1, "|", 0},
        {17, 1, "|", 0},
        {18, 1, "|", 0},
        {18, 1, "|", 0},
        {2, 68, "|", 0},
        {3, 68, "|", 0},
        {4, 68, "|", 0},
        {5, 68, "|", 0},
        {6, 68, "|", 0},
        {7, 68, "|", 0},
        {8, 68, "|", 0},
        {9, 68, "|", 0},
        {10, 68, "|", 0},
        {11, 68, "|", 0},
        {12, 68, "|", 0},
        {13, 68, "|", 0},
        {14, 68, "|", 0},
        {15, 68, "|", 0},
        {16, 68, "|", 0},
        {17, 68, "|", 0},
        {18, 68, "|", 0},
        {19, 2, "------------------------------------------------------------------", 0},

    };

    
    bool czyMenuJestWlaczone = true;

    
    srand(time(NULL));

    // tablica przechowujaca pozycje przenoszenia pionkÄ?A?w
    int pozycjePrzenoszeniaPionkow[2];
    pozycjePrzenoszeniaPionkow[0] = -1;
    pozycjePrzenoszeniaPionkow[1] = -1;

    
    int wybranePole = 0;
    int nrPozycjiZapisanej = 0;
    bool czyKostkaAUzyta = false;
    bool czyKostkaBUzyta = false;
    Stos stosy[LICZBA_STOSOW];
    int graczID = 2;

    
    for (int i = 0; i < LICZBA_STOSOW; i++)
        inicjalizujStos(&stosy[i]);

    
    for (int i = 0; i < 2; i++)
        wrzucNaStos(&stosy[0], 1);

    for (int i = 0; i < 5; i++)
        wrzucNaStos(&stosy[5], 2);

    for (int i = 0; i < 3; i++)
        wrzucNaStos(&stosy[7], 2);

    for (int i = 0; i < 5; i++)
        wrzucNaStos(&stosy[11], 1);

    for (int i = 0; i < 5; i++)
        wrzucNaStos(&stosy[12], 2);

    for (int i = 0; i < 3; i++)
        wrzucNaStos(&stosy[16], 1);

    for (int i = 0; i < 5; i++)
        wrzucNaStos(&stosy[18], 1);

    for (int i = 0; i < 2; i++)
        wrzucNaStos(&stosy[23], 2);

    // inicjalizacja interfejsu uÄ¹Ä1ytkownika
    initscr();
    start_color();
    
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    noecho();
    curs_set(0);

    WINDOW *w = newwin(23, 80, 4, 3);
    keypad(w, TRUE);
    wtimeout(w, 0);

    
    int kostkaA = rzutKostka();
    int kostkaB = rzutKostka();

    
    for (;;)
    {
        //odczyt klawisza
        int klawiatura = wgetch(w);

        if (czyMenuJestWlaczone)
        { 
            wattron(w, COLOR_PAIR(3));
            mvwprintw(w, 1, 1, "====== MENU UZYTKOWNIKA ======");
             wattroff(w, COLOR_PAIR(3));
            wattron(w, COLOR_PAIR(4));
            mvwprintw(w, 2, 1, "Filip Swiniarski  197725");
            mvwprintw(w, 3, 1, "Nacisnij (R) aby rozpoczac gre");
            wattroff(w, COLOR_PAIR(4));
            wattron(w, COLOR_PAIR(3));
            mvwprintw(w, 4, 1, "==============================");
            wattroff(w, COLOR_PAIR(3));
            wattron(w, COLOR_PAIR(1));
            mvwprintw(w, 5, 1, "Instrukcja sterowania programem:");
            wattroff(w, COLOR_PAIR(1));
            mvwprintw(w, 6, 1, "- Uzyj klawiszy strzalek lewo/prawo do wyboru pola.");
            mvwprintw(w, 7, 1, "- Nacisnij spacje, aby wybrac pole z ktorego przenosisz pion");
            mvwprintw(w, 8, 1, "  i docelowy dla pionka po ponownym nacisnieciu spacji.");

            mvwprintw(w, 9, 1, "- Rzucenie kostkami odbywa sie automatycznie na poczatku tury.");
            mvwprintw(w, 10, 1, "- Nacisnij klawisz 'z', aby zapisac stan gry.");
            mvwprintw(w, 11, 1, "- Nacisnij klawisz 'w', aby wczytac stan gry.");
    
            if ((klawiatura & A_CHARTEXT) == 'r')
            {
                czyMenuJestWlaczone = false;
            }
            wrefresh(w);

        }
        else
        {
            
            if ((klawiatura & A_CHARTEXT) == ' ')
            {
                
                pozycjePrzenoszeniaPionkow[nrPozycjiZapisanej] = wybranePole;
                nrPozycjiZapisanej++;

               
                if (nrPozycjiZapisanej == 2)
                {
                    nrPozycjiZapisanej = 0;

                    
                    if (przesunPionek(stosy, pozycjePrzenoszeniaPionkow[0], pozycjePrzenoszeniaPionkow[1], graczID, kostkaA, kostkaB, czyKostkaAUzyta, czyKostkaBUzyta))
                    {
                        // jesli kostki A i B zostaly uzyte, zmien gracza i rzut kostkami
                        if (czyKostkaAUzyta && czyKostkaBUzyta)
                        {
                            graczID = (graczID == 1) ? 2 : 1;
                            czyKostkaAUzyta = false;
                            czyKostkaBUzyta = false;
                            kostkaA = rzutKostka();
                            kostkaB = rzutKostka();
                        }
                        pozycjePrzenoszeniaPionkow[0] = pozycjePrzenoszeniaPionkow[1] = -1;
                    }
                    else
                    {
                        // jesli nie mozna przesunac pionka, zresetuj zapisane pozycje
                        pozycjePrzenoszeniaPionkow[0] = pozycjePrzenoszeniaPionkow[1] = -1;
                    }
                }
            }

            // przesuniecie pozycji gracza na planszy
            przesunPozycjeGracza(&wybranePole, klawiatura);

           
            werase(w);
            mvwprintw(w, 21, 1, "Wypadlo: %d, %d", kostkaA, kostkaB);

            if (graczID == 2)
                mvwprintw(w, 22, 1, "Kolej gracza X");
            else if (graczID == 1)
                mvwprintw(w, 22, 1, "Kolej gracza O");

           
            int dx = 0;

            
            for (int i = 0; i < LICZBA_STOSOW; i++)
            {
                for (int j = 0; j < rozmiarStosu(&stosy[i]); j++)
                {
                    char znakiDoWyswietlenia[2];
                    znakiDoWyswietlenia[0] = ' ';
                    if (pobierzElementZeStosu(&stosy[i], j) == 1)
                        znakiDoWyswietlenia[1] = 'O';
                    else if (pobierzElementZeStosu(&stosy[i], j) == 2)
                        znakiDoWyswietlenia[1] = 'X';

                 
                    if (i >= 0 && i < 6)
                        mvwprintw(w, 17 - j, 7 + 5 * (11 - i), "%s", znakiDoWyswietlenia);
                    else if (i >= 6 && i < 12)
                    {
                        mvwprintw(w, 17 - j, 7 + 5 * (10 - i) - 1, "%s", znakiDoWyswietlenia);
                    }
                    else if (i >= 12 && i < 18)
                    {
                        mvwprintw(w, 3 + j, 1 + dx, "%s", znakiDoWyswietlenia);
                    }
                    else if (i >= 18 && i < 24)
                    {
                        mvwprintw(w, 3 + j, 1 + dx + 6, "%s", znakiDoWyswietlenia);
                    }
                }
                if (i >= 12)
                    dx = dx + 5;
            }

            
            mvwprintw(w, 20, 1, "Aby zapisac rozgrywke wcisnij 'z', w celu wczytania 'w'");

            // obsluga zapisu stanu gry
            if ((klawiatura & A_CHARTEXT) == 'z')
                zapiszStan(stosy, graczID, kostkaA, kostkaB);

            // obsluga wczytywania stanu gry
            if ((klawiatura & A_CHARTEXT) == 'w')
                wczytajStan(stosy, &graczID, &kostkaA, &kostkaB);

         
            wyswietlPlansze(elementy, pozycjePrzenoszeniaPionkow, &wybranePole, w);
        }

        
        wrefresh(w);

        
        napms(16);
    }
}
