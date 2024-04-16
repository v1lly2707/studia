#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

// konfiguracja okna
#define SZEROKOSC_EKRANU 640
#define WYSOKOSC_EKRANU 480

#define PREDKOSC_MARIO 2.5      // predkosc chodzenia
#define PREDKOSC_SKOKU_MARIO -6 // predkosc odbicia od podloza
#define GRAWITACJA 0.4          // jak szybko mario spada

// ustawiony rozmiar postaci mario 16 pikseli na 16 pikseli
#define MARIO_SPRITE_WYSOKOSC 16
#define MARIO_SPRITE_DLUGOSC 16

// pozycja obrazka platformy w spritesheetcie
#define POZYCJA_SPRITE_PLATFORMY_X 87
#define POZYCJA_SPRITE_PLATFORMY_Y 193
// rozmiar platformy w spritesheetcie
#define DLUGOSC_SPRITE_PLATFORMY 16
#define WYSOKOSC_SPRITE_PLATFORMY 8

// jak dlugo trwa jedna klatka animacji zanim zostanie przelaczona do nastepnej
#define CZAS_TRWANIA_KLATKI_ANIMACJI 0.4


typedef enum {
    OPCJA_MENU_WYJSCIE,
    OPCJA_MENU_SPRAWDZ_WYNIKI,
    OPCJA_MENU_WYBIERZ_ETAP,
    OPCJA_MENU_LICZBA
} OpcjaMenu;

typedef enum {
    STAN_GRY_GRA,
    STAN_GRY_ZAPYTANIE_KONTYNUACJI,
    STAN_GRY_MENU,
    STAN_GRY_WYGRANA
} StanGry;

typedef enum {
    STAN_MARIO_BEZCZYNNY,
    STAN_MARIO_CHODZENIE,
    STAN_MARIO_SKAKANIE,
    STAN_MARIO_WSPINANIE
} StanMario;

typedef enum { MARIO_KIERUNEK_LEWO, MARIO_KIERUNEK_PRAWO } KierunekMario;

typedef struct {
    int x, y;
    int predkoscX;
    int szerokosc, wysokosc;
    double czasAnimacji;
    int punktNawigacyjnyStart_X, punktNawigacyjnyKoniec_X;
    int czyPrzesuwaWPrawo;
    int indeksKlatki;
} Beczka;

typedef struct {
    int x, y, szerokosc, wysokosc;
} Platforma;

typedef struct {
    int x, y, szerokosc, wysokosc;
} Drabina;

typedef struct {
    double x, y;
    double predkoscX, predkoscY;
    int czyNaPlatformie;
    int czyNaDrabinie;
    int PozYGraczaNaDrabinie;
    StanMario stan;
    KierunekMario kierunek;
    double czasAnimacji = 0;
    int liczbaZyc;
    int czyKolizja;
    double czasGry;
} Mario;

typedef struct {
    int x, y;
    SDL_Surface* obraz;
} Serce;

typedef struct {
    int wybranaOpcja;
    int czyMenuJestAktywne;
} Menu;

StanGry stanGry = STAN_GRY_GRA;

// zmienne ktore bêd¹ przechowywaæ wartoœci kolorów do wyswietlania napisow
Uint32 kolorCzerwony, kolorZielony, kolorZolty, kolorBrazowy, kolorRozowy;

int iloscPlatform;
int iloscDrabin;
int iloscBeczek;
int aktualnyEtap = 1;

Menu menu = { 0, 0 };
SDL_Rect pozycjaElementuZakonczeniaEtapu = { 0, 0, 0, 0 };

Platforma* platformy = NULL;
Drabina* drabiny = NULL;
Beczka* beczki = NULL;

const int MAX_DLUGOSC_PSEUDONIMU = 200;
char pseudonimGracza[MAX_DLUGOSC_PSEUDONIMU] = "";
int dlugoscPseudonimu = 0;
int zmPomocniczaPozYDrabina = 0;
int indeksKlatki = 0;

// pozycjaX w spritesheet_serduszka , pozycjaY w spritesheet_serduszka, szerokosc, wysokosc
int SerceSpritesheetPozycja[4] = { 93, 77, 15, 13 };
int MarioSpritesheetPozycje[11][4] = {
    {56, 2, 12, 16},    {79, 2, 15, 16},    {103, 3, 15, 15},
    {158, 160, 12, 16}, {132, 160, 15, 16}, {108, 161, 15, 15},
    {78, 49, 16, 15}, {132, 207, 16, 15},
    {128, 2, 13, 16},   {151, 3, 14, 15}, {174, 5, 16, 12},
};
int BeczkaSpritesheetPozycje[11][4] = {
    {88, 91, 12, 10}, {112, 91, 12, 10}, {136, 91, 12, 10}, {160, 91, 12, 10} };

void RysujObrazekZSpritesheet(SDL_Surface* ekran, SDL_Surface* spritesheet,
    int pozycjaX_spritesheet, int pozycjaY_spritesheet, int szerokosc_obrazu, int wysokosc_obrazu,
    int pozycjaDocelowaX, int pozycjaDocelowaY) {
    SDL_Rect prostokatZrodlowy;
    SDL_Rect prostokatDocelowy;

    prostokatZrodlowy.x = pozycjaX_spritesheet;
    prostokatZrodlowy.y = pozycjaY_spritesheet;
    prostokatZrodlowy.w = szerokosc_obrazu;
    prostokatZrodlowy.h = wysokosc_obrazu;

    prostokatDocelowy.x = pozycjaDocelowaX;
    prostokatDocelowy.y = pozycjaDocelowaY;
    prostokatDocelowy.w = szerokosc_obrazu;
    prostokatDocelowy.h = wysokosc_obrazu;

    SDL_BlitSurface(spritesheet, &prostokatZrodlowy, ekran, &prostokatDocelowy);
}

bool SprawdzKolizjeMarioZKoniecEtapu(const Mario& mario) {
    SDL_Rect pozycjaMario = { static_cast<int>(mario.x), static_cast<int>(mario.y),
                          16, 16 };
    if (SDL_HasIntersection(&pozycjaMario, &pozycjaElementuZakonczeniaEtapu)) {
        return true;
    }
    return false;
}
 
void InicjalizujGraczaMario(Mario* mario) {
    mario->x = 30;
    mario->stan = STAN_MARIO_BEZCZYNNY;
    mario->kierunek = MARIO_KIERUNEK_PRAWO;
    mario->liczbaZyc = 8;
    mario->czasGry = 0;
    mario->y = WYSOKOSC_EKRANU - 50;
    mario->predkoscX = 0;
    mario->predkoscY = 0;
    mario->czyNaPlatformie = 1;
    mario->czyNaDrabinie = 0;
    mario->PozYGraczaNaDrabinie = 0;
    mario->czasAnimacji = 0;
    mario->czyKolizja = 0;

}

void ZainicjujEtap01(Platforma** platformy, Drabina** drabiny, Beczka** beczki) {
    aktualnyEtap = 1;

    iloscPlatform = 10;
    iloscDrabin = 9;
    iloscBeczek = 5;

    pozycjaElementuZakonczeniaEtapu = { 450, 52, 16, 16 };
    static Platforma tymczasowePlatformy[] = {
        {0, WYSOKOSC_EKRANU - 30, SZEROKOSC_EKRANU, 8},
        {30, 380, 400, 8},
        {130, 300, 200, 8},
        {530, 240, 70, 8},
        {200, 160, 70, 8},
        {200, 120, 70, 8},
        {200, 80, 70, 8},
        {30, 300, 40, 8},
        {20, 200, 150, 8},
        {320, 70, 250, 8},
    };
    *platformy = new Platforma[iloscPlatform];
    memcpy(*platformy, tymczasowePlatformy, sizeof(tymczasowePlatformy));

    static Drabina tymczasoweDrabiny[] = {
        {60, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {160, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {260, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {360, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {540, WYSOKOSC_EKRANU - 110 - 16 - 40 - 70 - 180, 10, 16 * 6 + 80},
        {560, WYSOKOSC_EKRANU - 110 - 16 - 50 - 70, 10, 16 * 6 + 110},
        {30, 300, 10, 60},
        {140, 200, 10, 60},
        {220, 70, 10, 40},
    };
    *drabiny = new Drabina[iloscDrabin];
    memcpy(*drabiny, tymczasoweDrabiny, sizeof(tymczasoweDrabiny));

    static Beczka tymczasoweBeczki[] = {
        {24, WYSOKOSC_EKRANU - 110, 2, 20, 20, 0.0, 24, 415, 1},
        {120, WYSOKOSC_EKRANU - 191, 2, 20, 20, 0.0, 120, 330, 1},
        {460, WYSOKOSC_EKRANU - 43, 2, 20, 20, 0.0, 460, 630, 1},
        {20, WYSOKOSC_EKRANU - 291, 2, 20, 20, 0.0, 20, 160, 1},
        {520, WYSOKOSC_EKRANU - 252, 2, 20, 20, 0.0, 520, 600, 1},
    };
    *beczki = new Beczka[iloscBeczek];
    memcpy(*beczki, tymczasoweBeczki, sizeof(tymczasoweBeczki));
}

void ZainicjujEtap02(Platforma** platformy, Drabina** drabiny, Beczka** beczki) {
    aktualnyEtap = 2;

    iloscPlatform = 6;
    iloscDrabin = 7; 
    iloscBeczek = 5;

    pozycjaElementuZakonczeniaEtapu = { 500, 35, 16, 16 };

    static Platforma tymczasowePlatformy[] = {
        {0, WYSOKOSC_EKRANU - 30, SZEROKOSC_EKRANU, 8},
        {100, WYSOKOSC_EKRANU - 80 * 1 - 30, SZEROKOSC_EKRANU - 200, 8},

        {200, WYSOKOSC_EKRANU - 80 * 2 - 30, SZEROKOSC_EKRANU - 300, 8},
        {300, WYSOKOSC_EKRANU - 80 * 3 - 30, SZEROKOSC_EKRANU - 400, 8},
        {400, WYSOKOSC_EKRANU - 80 * 4 - 30, SZEROKOSC_EKRANU - 500, 8},

        {500, WYSOKOSC_EKRANU - 80 * 5 - 30, SZEROKOSC_EKRANU - 600, 8},

    };
    *platformy = new Platforma[iloscPlatform];
    memcpy(*platformy, tymczasowePlatformy, sizeof(tymczasowePlatformy));

    static Drabina tymczasoweDrabiny[] = {
        {160, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {260, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {360, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {230, 280, 10, 81},
        {340, 200, 10, 80},
        {420, 110, 10, 81},
        {520, 40, 10, 81},
    };
    *drabiny = new Drabina[iloscDrabin];
    memcpy(*drabiny, tymczasoweDrabiny, sizeof(tymczasoweDrabiny));

    static Beczka tymczasoweBeczki[] = {
        {460, WYSOKOSC_EKRANU - 43, 2, 20, 20, 0.0, 460, 630, 1},

        {110, WYSOKOSC_EKRANU - 125, 2, 20, 20, 0.0, 110, 415, 1},
        {200, WYSOKOSC_EKRANU - 204, 2, 20, 20, 0.0, 200, 330, 1},
        {320, WYSOKOSC_EKRANU - 282, 2, 20, 20, 0.0, 320, 530, 1},

        {395, WYSOKOSC_EKRANU - 364, 2, 20, 20, 0.0, 395, 500, 1},
    };
    *beczki = new Beczka[iloscBeczek];
    memcpy(*beczki, tymczasoweBeczki, sizeof(tymczasoweBeczki));
}

void ZainicjujEtap03(Platforma** platformy, Drabina** drabiny, Beczka** beczki) {
    aktualnyEtap = 3;
    
    iloscPlatform = 6;
    iloscDrabin = 7;
    iloscBeczek = 5;

    pozycjaElementuZakonczeniaEtapu = { 500, 35, 16, 16 };

    static Platforma tymczasowePlatformy[] = {

        {0, WYSOKOSC_EKRANU - 30, SZEROKOSC_EKRANU, 8},

        {100, WYSOKOSC_EKRANU - 80 * 1 - 30, SZEROKOSC_EKRANU - 200, 8},

        {200, WYSOKOSC_EKRANU - 80 * 2 - 30, SZEROKOSC_EKRANU - 400, 8},

        {300, WYSOKOSC_EKRANU - 80 * 5 - 25, SZEROKOSC_EKRANU - 340, 8},

        {100, WYSOKOSC_EKRANU - 80 * 4 - 10, 150, 8},
        {300, WYSOKOSC_EKRANU - 80 * 4 - 10, 150, 8},

    };

    *platformy = new Platforma[iloscPlatform];
    memcpy(*platformy, tymczasowePlatformy, sizeof(tymczasowePlatformy));

    static Drabina tymczasoweDrabiny[] = {
        {210, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {360, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {510, WYSOKOSC_EKRANU - 110, 10, 16 * 5 - 10},
        {280, 280, 10, 81},
        {230, 130, 10, 150},
        {440, 40, 10, 91},
    };
    *drabiny = new Drabina[iloscDrabin];
    memcpy(*drabiny, tymczasoweDrabiny, sizeof(tymczasoweDrabiny));

    static Beczka tymczasoweBeczki[] = {
        {200, WYSOKOSC_EKRANU - 43, 2, 20, 20, 0.0, 200, 600, 1},
        {160, WYSOKOSC_EKRANU - 125, 2, 20, 20, 0.0, 160, 465, 1},
        {210, WYSOKOSC_EKRANU - 204, 2, 20, 20, 0.0, 210, 380, 1},
        {300, WYSOKOSC_EKRANU - 342, 2, 20, 20, 0.0, 300, 450, 1},
        {310, WYSOKOSC_EKRANU - 432, 2, 20, 20, 0.0, 310, 500, 1},
    };
    *beczki = new Beczka[iloscBeczek];
    memcpy(*beczki, tymczasoweBeczki, sizeof(tymczasoweBeczki));
}
 
void RysujElementZakonczeniaEtapuETI(SDL_Surface* ekran, SDL_Surface* eti) {
    SDL_Rect prostokat;
    prostokat.x = pozycjaElementuZakonczeniaEtapu.x;
    prostokat.y = pozycjaElementuZakonczeniaEtapu.y;
    prostokat.w = pozycjaElementuZakonczeniaEtapu.w;
    prostokat.h = pozycjaElementuZakonczeniaEtapu.h;
    SDL_BlitSurface(eti, NULL, ekran, &prostokat);
}

void RysujPixel(SDL_Surface* surface, int x, int y, Uint32 kolor) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = kolor;
}

void NarysujKolorowyNapis(SDL_Surface* ekran, int x, int y, const char* tekst,
    SDL_Surface* zestawZnakow, Uint32 kolor) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;

    if (SDL_MUSTLOCK(ekran)) {
        SDL_LockSurface(ekran);
    }

    while (*tekst) {
        c = *tekst & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(zestawZnakow, &s, ekran, &d);

        for (int i = 0; i < s.w; i++) {
            for (int j = 0; j < s.h; j++) {
                Uint32* pixel =
                    (Uint32*)((Uint8*)ekran->pixels +
                        (d.y + j) * ekran->pitch + (d.x + i) * 4);
                if (*pixel != SDL_MapRGB(ekran->format, 0, 0, 0)) {
                    *pixel = kolor;
                }
            }
        }

        x += 8;
        tekst++;
    }

    if (SDL_MUSTLOCK(ekran)) {
        SDL_UnlockSurface(ekran);
    }
}

void NarysujMenuUzytkownika(SDL_Surface* ekran, SDL_Surface* zestawZnakow) {
    const char* opcjeMenu[OPCJA_MENU_LICZBA] = {
        "Wyjscie", "Sprawdzenie wynikow/Zapis i odczyt", "Wybor etapu" };

    for (int i = 0; i < OPCJA_MENU_LICZBA; i++) {
        Uint32 kolorNapisu = (i == menu.wybranaOpcja) ? kolorCzerwony : kolorZielony;
        NarysujKolorowyNapis(ekran, 100, 100 + i * 20, opcjeMenu[i], zestawZnakow, kolorNapisu);
    }
    NarysujKolorowyNapis(ekran, 100, 243,
        "Sterowanie: strzalka prawo/lewo - chodzenie,", zestawZnakow,
        kolorRozowy);
    NarysujKolorowyNapis(ekran, 100, 253,
        "strzalka gora/dol - wchodzenie/schodzenie z drabiny,", zestawZnakow,
        kolorRozowy);
    NarysujKolorowyNapis(ekran, 100, 263,
        "spacja - skok, ESC - wyjscie z gry, n - nowa rozgrywka", zestawZnakow,
        kolorRozowy);
    NarysujKolorowyNapis(ekran, 100, 183,
        "Wpisz za pomoca przyciskow klawiatury swoj nick:", zestawZnakow,
        kolorBrazowy);

    NarysujKolorowyNapis(ekran, 100, 200, pseudonimGracza, zestawZnakow, kolorZolty);
}

void NarysujMenuEtapy(SDL_Surface* ekran, SDL_Surface* zestawZnakow) {
    const char* opcjeMenu[OPCJA_MENU_LICZBA] = { "ETAP 1", "ETAP 2", "ETAP 3" };

    for (int i = 0; i < OPCJA_MENU_LICZBA; i++) {
        Uint32 kolorNapisu = (i == menu.wybranaOpcja) ? kolorCzerwony : kolorZielony;
        NarysujKolorowyNapis(ekran, 100, 100 + i * 20, opcjeMenu[i], zestawZnakow, kolorNapisu);
    }
}

void WypiszBrakImplementacji(SDL_Surface* ekran, SDL_Surface* zestawZnakow) {
    menu.wybranaOpcja = 0;
    const char* opcjeMenu[1] = {
        "BRAK IMPLEMENTACJI NACISNIJ 'ENTER' ABY POWROCIC DO MENU",
    };

    for (int i = 0; i < 1; i++) {
        Uint32 kolorNapisu = (i == menu.wybranaOpcja) ? kolorCzerwony : kolorZielony;
        NarysujKolorowyNapis(ekran, 50, 100 + i * 20, opcjeMenu[i], zestawZnakow, kolorNapisu);
    }
}

void ObslugujZdarzenieMenu(SDL_Event* event, Menu* menu, int* czyZakonczycGre, Mario* mario) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_UP:
            menu->wybranaOpcja =
                (menu->wybranaOpcja - 1 + OPCJA_MENU_LICZBA) %
                OPCJA_MENU_LICZBA;
            break;
        case SDLK_DOWN:
            menu->wybranaOpcja =
                (menu->wybranaOpcja + 1) % OPCJA_MENU_LICZBA;
            break;
        case SDLK_RETURN:
            if (menu->czyMenuJestAktywne == 1) {
                switch (menu->wybranaOpcja) {
                case OPCJA_MENU_WYJSCIE:
                    *czyZakonczycGre = 1;
                    break;
                case OPCJA_MENU_SPRAWDZ_WYNIKI:
                    menu->czyMenuJestAktywne = 3;
                    menu->wybranaOpcja = 0;
                    break;
                case OPCJA_MENU_WYBIERZ_ETAP:
                    menu->czyMenuJestAktywne = 2;
                    menu->wybranaOpcja = 0;

                    break;
                }
            }
            else if (menu->czyMenuJestAktywne == 2) {
                switch (menu->wybranaOpcja) {
                case OPCJA_MENU_WYJSCIE:
                    ZainicjujEtap01(&platformy, &drabiny, &beczki);
                    InicjalizujGraczaMario(mario);
                    stanGry = STAN_GRY_GRA;
                    menu->czyMenuJestAktywne = 0;
                    menu->wybranaOpcja = 0;

                    break;
                case OPCJA_MENU_SPRAWDZ_WYNIKI:
                    ZainicjujEtap02(&platformy, &drabiny, &beczki);
                    InicjalizujGraczaMario(mario);
                    stanGry = STAN_GRY_GRA;
                    menu->czyMenuJestAktywne = 0;
                    menu->wybranaOpcja = 0;
                    break;
                case OPCJA_MENU_WYBIERZ_ETAP:
                    ZainicjujEtap01(&platformy, &drabiny, &beczki);
                    InicjalizujGraczaMario(mario);
                    stanGry = STAN_GRY_GRA;
                    menu->czyMenuJestAktywne = 0;
                    menu->wybranaOpcja = 0;

                    break;
                }
            }
            else if (menu->czyMenuJestAktywne == 3) {
                switch (menu->wybranaOpcja) {
                case OPCJA_MENU_WYJSCIE:
                    menu->czyMenuJestAktywne = 1;
                    menu->wybranaOpcja = 0;
                    break;
                }
            }
            break;
        case SDLK_ESCAPE:
            *czyZakonczycGre = 1;
            break;
        case SDLK_BACKSPACE:
            if (dlugoscPseudonimu > 0) {
                pseudonimGracza[--dlugoscPseudonimu] = '\0';
            }
            break;
        }
    }
    else if (event->type == SDL_TEXTINPUT &&
        dlugoscPseudonimu < MAX_DLUGOSC_PSEUDONIMU - 1 &&
        stanGry == STAN_GRY_MENU) {
        size_t charLen = strlen(event->text.text);
        if (dlugoscPseudonimu + charLen < MAX_DLUGOSC_PSEUDONIMU) {
            strcat(pseudonimGracza, event->text.text);
            dlugoscPseudonimu += charLen;
        }
    }
}

bool SprawdzKolizjeMarioZBeczka(Mario* mario, Beczka* beczka) {
    if (mario->x + 14 > beczka->x && mario->x < beczka->x + beczka->szerokosc &&
        mario->y + 14 > beczka->y && mario->y < beczka->y + beczka->wysokosc) {
        return true;
    }
    return false;
}
 
void RysujPostacMario(SDL_Surface* ekran, SDL_Surface* mario_spritesheet,
    Mario* mario) {
    if (mario->stan == STAN_MARIO_WSPINANIE) {
        if (mario->czyNaDrabinie) {
            int indeksUzywanejGrafiki = 8;
            if (mario->y != zmPomocniczaPozYDrabina) {
                zmPomocniczaPozYDrabina = mario->y;
                int indeksKlatkiWspinaczki =
                    static_cast<int>(mario->czasAnimacji /
                        CZAS_TRWANIA_KLATKI_ANIMACJI) %
                    2;
                indeksUzywanejGrafiki = 8 + indeksKlatkiWspinaczki;
            }

            RysujObrazekZSpritesheet(
                ekran, mario_spritesheet, MarioSpritesheetPozycje[indeksUzywanejGrafiki][0],
                MarioSpritesheetPozycje[indeksUzywanejGrafiki][1],
                MarioSpritesheetPozycje[indeksUzywanejGrafiki][2],
                MarioSpritesheetPozycje[indeksUzywanejGrafiki][3], mario->x, mario->y);
        }
    }

    if (mario->stan == STAN_MARIO_CHODZENIE) {
        indeksKlatki =
            static_cast<int>(mario->czasAnimacji / CZAS_TRWANIA_KLATKI_ANIMACJI) %
            3;

        if (mario->kierunek == MARIO_KIERUNEK_LEWO)
            RysujObrazekZSpritesheet(
                ekran, mario_spritesheet, MarioSpritesheetPozycje[indeksKlatki][0],
                MarioSpritesheetPozycje[indeksKlatki][1], MarioSpritesheetPozycje[indeksKlatki][2],
                MarioSpritesheetPozycje[indeksKlatki][3], mario->x, mario->y);

        if (mario->kierunek == MARIO_KIERUNEK_PRAWO)
            RysujObrazekZSpritesheet(
                ekran, mario_spritesheet, MarioSpritesheetPozycje[3 + indeksKlatki][0],
                MarioSpritesheetPozycje[3 + indeksKlatki][1],
                MarioSpritesheetPozycje[3 + indeksKlatki][2],
                MarioSpritesheetPozycje[3 + indeksKlatki][3], mario->x, mario->y);
    }

    if (mario->stan == STAN_MARIO_BEZCZYNNY) {
        if (mario->kierunek == MARIO_KIERUNEK_LEWO)
            RysujObrazekZSpritesheet(ekran, mario_spritesheet,
                MarioSpritesheetPozycje[0][0], MarioSpritesheetPozycje[0][1],
                MarioSpritesheetPozycje[0][2], MarioSpritesheetPozycje[0][3],
                mario->x, mario->y);

        if (mario->kierunek == MARIO_KIERUNEK_PRAWO)
            RysujObrazekZSpritesheet(ekran, mario_spritesheet,
                MarioSpritesheetPozycje[3][0], MarioSpritesheetPozycje[3][1],
                MarioSpritesheetPozycje[3][2], MarioSpritesheetPozycje[3][3],
                mario->x, mario->y);
    }

    if (mario->stan == STAN_MARIO_SKAKANIE) {
        if (mario->kierunek == MARIO_KIERUNEK_LEWO)
            RysujObrazekZSpritesheet(ekran, mario_spritesheet,
                MarioSpritesheetPozycje[6][0], MarioSpritesheetPozycje[6][1],
                MarioSpritesheetPozycje[6][2], MarioSpritesheetPozycje[6][3],
                mario->x, mario->y);

        if (mario->kierunek == MARIO_KIERUNEK_PRAWO)
            RysujObrazekZSpritesheet(ekran, mario_spritesheet,
                MarioSpritesheetPozycje[7][0], MarioSpritesheetPozycje[7][1],
                MarioSpritesheetPozycje[7][2], MarioSpritesheetPozycje[7][3],
                mario->x, mario->y);
    }
}

void ObslugujKlawiature(SDL_Event* event, Mario* mario, int* czyZakonczycGre, double* czas) {
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
        switch (event->key.keysym.sym) {
        case SDLK_1:
            ZainicjujEtap01(&platformy, &drabiny, &beczki);
            InicjalizujGraczaMario(mario);
            stanGry = STAN_GRY_GRA;
            break;

        case SDLK_2:
            ZainicjujEtap02(&platformy, &drabiny, &beczki);
            InicjalizujGraczaMario(mario);
            stanGry = STAN_GRY_GRA;
            break;

        case SDLK_3:
            ZainicjujEtap03(&platformy, &drabiny, &beczki);
            InicjalizujGraczaMario(mario);
            stanGry = STAN_GRY_GRA;
            break;
        case SDLK_LEFT:
            mario->predkoscX = -PREDKOSC_MARIO;
            mario->stan = STAN_MARIO_CHODZENIE;
            mario->kierunek = MARIO_KIERUNEK_LEWO;
            break;
        case SDLK_RIGHT:
            mario->predkoscX = PREDKOSC_MARIO;
            mario->stan = STAN_MARIO_CHODZENIE;
            mario->kierunek = MARIO_KIERUNEK_PRAWO;
            break;
        case SDLK_ESCAPE:
            *czyZakonczycGre = 1;
            break;
        case SDLK_k:
            stanGry = STAN_GRY_GRA;
            break;
        case SDLK_m:
            menu.czyMenuJestAktywne = 1;
            menu.wybranaOpcja = 0;

            stanGry = STAN_GRY_MENU;

            break;
        case SDLK_n:
            InicjalizujGraczaMario(mario);
            *czas = 0.0;
            break;
        case SDLK_SPACE:
            if (mario->czyNaPlatformie) {
                mario->predkoscY = PREDKOSC_SKOKU_MARIO;
                mario->czyNaPlatformie = 0;
                mario->stan = STAN_MARIO_SKAKANIE;
            }
            break;
        case SDLK_UP:
            for (int i = 0; i < iloscDrabin; i++) {
                Drabina ladder = drabiny[i];
                if (mario->x + 13 > ladder.x &&
                    mario->x < ladder.x + ladder.szerokosc &&
                    mario->y + 16 > ladder.y &&
                    mario->y < ladder.y + ladder.wysokosc) {
                    mario->czyNaDrabinie = 1;
                    mario->predkoscY = 0;
                    break;
                }
            }
            break;
        }
    }
    else if (event->type == SDL_KEYUP) {
        mario->czasAnimacji = 0;

        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
            mario->predkoscX = 0;
            mario->stan = STAN_MARIO_BEZCZYNNY;
            mario->czasAnimacji = 0;
            indeksKlatki = 0;
            break;
        }
    }

    if (mario->czyNaDrabinie) {
        if (event->type == SDL_KEYDOWN) {
            switch (event->key.keysym.sym) {
            case SDLK_UP:
                mario->y -= 3;
                break;

            case SDLK_DOWN:
                mario->y += 3;
                break;
            }
        }
    }
}

bool SprawdzKolizjeMarioZDrabina(Mario* mario, Drabina* drabiny, int iloscDrabin) {
    for (int i = 0; i < iloscDrabin; i++) {
        Drabina drabina = drabiny[i];
        if (mario->x + MARIO_SPRITE_DLUGOSC > drabina.x &&
            mario->x < drabina.x + drabina.szerokosc &&
            mario->y + MARIO_SPRITE_WYSOKOSC > drabina.y &&
            mario->y < drabina.y + drabina.wysokosc) {
            return true;
        }
    }
    return false;
}
void AktualizujGre(Mario* mario, double deltaTime) {
    mario->x += mario->predkoscX;
    int czyWystapilaKolizja = 0;

    if (SprawdzKolizjeMarioZKoniecEtapu(*mario)) {
        if (aktualnyEtap == 1) {
            ZainicjujEtap02(&platformy, &drabiny, &beczki);
            InicjalizujGraczaMario(mario);
            stanGry = STAN_GRY_GRA;
        }
        else if (aktualnyEtap == 2) {
            ZainicjujEtap03(&platformy, &drabiny, &beczki);
            InicjalizujGraczaMario(mario);
            stanGry = STAN_GRY_GRA;
        }
        else if (aktualnyEtap == 3) {
            stanGry = STAN_GRY_WYGRANA;
        }

        return;
    }
    bool czyJestNaDrabinie = SprawdzKolizjeMarioZDrabina(mario, drabiny, iloscDrabin);
    if (mario->x < 0) mario->x = 0;
    if (mario->x > SZEROKOSC_EKRANU - MARIO_SPRITE_DLUGOSC)
        mario->x = SZEROKOSC_EKRANU - MARIO_SPRITE_DLUGOSC;
    if (mario->czyNaPlatformie && mario->stan == STAN_MARIO_SKAKANIE) {
        if (mario->predkoscX == 0) {
            mario->stan = STAN_MARIO_BEZCZYNNY;
        }
        else {
            mario->stan = STAN_MARIO_CHODZENIE;
        }
    }

    if (!czyJestNaDrabinie && mario->stan == STAN_MARIO_WSPINANIE) {
        mario->stan =
            (mario->predkoscX == 0) ? STAN_MARIO_BEZCZYNNY : STAN_MARIO_CHODZENIE;
    }
    if (!czyJestNaDrabinie) {
        mario->predkoscY += GRAWITACJA;
        mario->y += mario->predkoscY;

        bool czyStoiNaPlatformie = false;
        for (int i = 0; i < iloscPlatform; i++) {
            Platforma ground = platformy[i];
            if (mario->y + MARIO_SPRITE_WYSOKOSC > ground.y &&
                mario->y < ground.y + ground.wysokosc &&
                mario->x + MARIO_SPRITE_DLUGOSC > ground.x &&
                mario->x < ground.x + ground.szerokosc) {
                if (mario->predkoscY > 0 && mario->y - mario->predkoscY < ground.y) {
                    mario->y = ground.y - MARIO_SPRITE_WYSOKOSC;
                    mario->predkoscY = 0;
                    czyStoiNaPlatformie = true;
                }

                if (mario->predkoscY < 0 &&
                    mario->y - mario->predkoscY > ground.y + ground.wysokosc) {
                    mario->y = ground.y + ground.wysokosc;
                    mario->predkoscY = 0;
                }
            }
        }
        mario->czyNaPlatformie = czyStoiNaPlatformie;
    }
    else {
        mario->predkoscY = 0;
        mario->stan = STAN_MARIO_WSPINANIE;
    }

    mario->czasAnimacji += deltaTime * 3;

    mario->czyNaDrabinie = czyJestNaDrabinie;

    for (int i = 0; i < iloscBeczek; i++) {
        if (SprawdzKolizjeMarioZBeczka(mario, &beczki[i])) {
            czyWystapilaKolizja = 1;
            if (!mario->czyKolizja) {
                mario->liczbaZyc--;
                mario->czyKolizja = 1;
                if (mario->liczbaZyc <= 0) {
                    stanGry = STAN_GRY_MENU;
                    menu.czyMenuJestAktywne = 1;

                }
                else if (czyWystapilaKolizja) {
                    stanGry = STAN_GRY_ZAPYTANIE_KONTYNUACJI;
                }
            }
            break;
        }
    }

    if (!czyWystapilaKolizja && mario->czyKolizja) {
        mario->czyKolizja = 0;
    }
}

void RysujPlatformy(SDL_Surface* ekran, SDL_Surface* spritesheet_platformy,
    Platforma platformy[], int iloscPlatform) {
    for (int i = 0; i < iloscPlatform; i++) {
        Platforma platforma = platformy[i];
        for (int x = platforma.x; x < platforma.x + platforma.szerokosc;
            x += DLUGOSC_SPRITE_PLATFORMY) {
            RysujObrazekZSpritesheet(ekran, spritesheet_platformy, POZYCJA_SPRITE_PLATFORMY_X,
                POZYCJA_SPRITE_PLATFORMY_Y, DLUGOSC_SPRITE_PLATFORMY,
                WYSOKOSC_SPRITE_PLATFORMY, x, platforma.y);
        }
    }
}

void RysujNapis(SDL_Surface* ekran, int x, int y, const char* tekst,
    SDL_Surface* zestawZnakow) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*tekst) {
        c = *tekst & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(zestawZnakow, &s, ekran, &d);
        x += 8;
        tekst++;
    };
};

void RysujSurface(SDL_Surface* ekran, SDL_Surface* sprite, int x, int y) {
    SDL_Rect prostokat;
    prostokat.x = x - sprite->w / 2;
    prostokat.y = y - sprite->h / 2;
    prostokat.w = sprite->w;
    prostokat.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, ekran, &prostokat);
};

void RysujLinie(SDL_Surface* ekran, int x, int y, int l, int dx, int dy,
    Uint32 color) {
    for (int i = 0; i < l; i++) {
        RysujPixel(ekran, x, y, color);
        x += dx;
        y += dy;
    };
};

void RysujProstokat(SDL_Surface* ekran, int x, int y, int l, int k,
    Uint32 kolorObrysu, Uint32 wypelnienieKolorem) {
    int i;
    RysujLinie(ekran, x, y, k, 0, 1, kolorObrysu);
    RysujLinie(ekran, x + l - 1, y, k, 0, 1, kolorObrysu);
    RysujLinie(ekran, x, y, l, 1, 0, kolorObrysu);
    RysujLinie(ekran, x, y + k - 1, l, 1, 0, kolorObrysu);
    for (i = y + 1; i < y + k - 1; i++)
        RysujLinie(ekran, x + 1, i, l - 2, 1, 0, wypelnienieKolorem);
};

void RysujDrabine(SDL_Surface* ekran, SDL_Surface* spritesheet_drabiny,
    Drabina* drabina) {
    int szerDrabiny = 10;
    int wysDrabiny = 16;
    int pozXSpritesheet = 81;
    int pozYSpritesheet = 194;

    for (int y = drabina->y; y < drabina->y + drabina->wysokosc;
        y += wysDrabiny) {
        RysujObrazekZSpritesheet(ekran, spritesheet_drabiny, pozXSpritesheet, pozYSpritesheet,
            szerDrabiny, wysDrabiny, drabina->x,
            y);
    }
}

void WyswietlCzasGry(SDL_Surface* ekran, double czasGry,
    SDL_Surface* zestawZnakow) {
    char tekst[50];
    sprintf(tekst, "Czas: %.1lf s", czasGry);
    RysujNapis(ekran, 10, 10, tekst, zestawZnakow);
}

void WyswietlNapisLiczbeZyc(SDL_Surface* ekran, SDL_Surface* zestawZnakow) {
    char tekst[50];
    sprintf(tekst, "Liczba zyc:");
    RysujNapis(ekran, 10, 30, tekst, zestawZnakow);
}

void AktualizujPozycjeBeczek(Beczka* beczki, int iloscBeczek, double deltaTime) {
    for (int i = 0; i < iloscBeczek; i++) {
        beczki[i].x += beczki[i].predkoscX * (beczki[i].czyPrzesuwaWPrawo ? 1 : -1);

        beczki[i].czasAnimacji += deltaTime;
        if (beczki[i].czasAnimacji >= CZAS_TRWANIA_KLATKI_ANIMACJI) {
            beczki[i].indeksKlatki = (beczki[i].indeksKlatki + 1) % 3;
            beczki[i].czasAnimacji = 0;
        }

        if (beczki[i].x >= beczki[i].punktNawigacyjnyKoniec_X) {
            beczki[i].x = beczki[i].punktNawigacyjnyKoniec_X;
            beczki[i].czyPrzesuwaWPrawo = 0;
        }
        else if (beczki[i].x <= beczki[i].punktNawigacyjnyStart_X) {
            beczki[i].x = beczki[i].punktNawigacyjnyStart_X;
            beczki[i].czyPrzesuwaWPrawo = 1;
        }
    }
}

void RysujBeczki(SDL_Surface* ekran, SDL_Surface* spritesheet_beczki,
    Beczka* beczki, int iloscBeczek) {
    for (int i = 0; i < iloscBeczek; i++) {
        int f = beczki[i].indeksKlatki;
        int pozX_spritesheet = BeczkaSpritesheetPozycje[f][0];
        int pozY_spritesheet = BeczkaSpritesheetPozycje[f][1];
        int dlugoscObrazu = BeczkaSpritesheetPozycje[f][2];
        int wysokoscObrazu = BeczkaSpritesheetPozycje[f][3];

        RysujObrazekZSpritesheet(ekran, spritesheet_beczki, pozX_spritesheet, pozY_spritesheet,
            dlugoscObrazu, wysokoscObrazu, beczki[i].x, beczki[i].y);
    }
}

void RysujObrazSerduszka(SDL_Surface* ekran, SDL_Surface* spritesheet_serduszka, int x, int y) {
    RysujObrazekZSpritesheet(ekran, spritesheet_serduszka, SerceSpritesheetPozycja[0], SerceSpritesheetPozycja[1],
        SerceSpritesheetPozycja[2], SerceSpritesheetPozycja[3], x, y);
}

#ifdef __cplusplus
extern "C"
#endif
int
main(int argc, char** argv) {
    int t1, t2, czyZakonczycGre, frames, rc;
    double delta, fpsTimer, fps, distance, etiSpeed;
    SDL_Event event;
    SDL_Surface* ekran, * zestawZnakow;
    SDL_Surface* elementZakonczeniaGryETI;
    SDL_Texture* scrtex;
    SDL_Window* okno;
    SDL_Renderer* renderer;
 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    rc = SDL_CreateWindowAndRenderer(SZEROKOSC_EKRANU, WYSOKOSC_EKRANU, 0, &okno,
        &renderer);
    if (rc != 0) {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        return 1;
    };

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SZEROKOSC_EKRANU, WYSOKOSC_EKRANU);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_SetWindowTitle(okno, "Zadanie DonkeyKong");

    ekran =
        SDL_CreateRGBSurface(0, SZEROKOSC_EKRANU, WYSOKOSC_EKRANU, 32, 0x00FF0000,
            0x0000FF00, 0x000000FF, 0xFF000000);

    scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, SZEROKOSC_EKRANU,
        WYSOKOSC_EKRANU);

    SDL_ShowCursor(SDL_DISABLE);

    kolorCzerwony = SDL_MapRGB(ekran->format, 0xFF, 0x00, 0x00);
    kolorZielony = SDL_MapRGB(ekran->format, 0x00, 0xFF, 0x00);
    kolorZolty = SDL_MapRGB(ekran->format, 0xFF, 0xCC, 0x00);
    kolorBrazowy = SDL_MapRGB(ekran->format, 0xCC, 0x77, 0x22);
    kolorRozowy = SDL_MapRGB(ekran->format, 0xAB, 0x47, 0x72);

    zestawZnakow = SDL_LoadBMP("./cs8x8.bmp");
    SDL_Surface* drabina_spritesheet = SDL_LoadBMP("4.bmp");
    if (drabina_spritesheet == NULL) {
    }
    if (zestawZnakow == NULL) {
        printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
        SDL_FreeSurface(ekran);
        SDL_DestroyTexture(scrtex);
        SDL_DestroyWindow(okno);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    };
    SDL_SetColorKey(zestawZnakow, true, 0x000000);

    elementZakonczeniaGryETI = SDL_LoadBMP("./eti.bmp");
    if (elementZakonczeniaGryETI == NULL) {
        printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
        SDL_FreeSurface(zestawZnakow);
        SDL_FreeSurface(ekran);
        SDL_DestroyTexture(scrtex);
        SDL_DestroyWindow(okno);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    };

    SDL_Surface* obrazekZycia = SDL_LoadBMP("5.bmp");
    if (obrazekZycia == NULL) {
        printf("SDL_LoadBMP(life.bmp) error: %s\n", SDL_GetError());
    }

    SDL_Surface* spritesheet_platformy = SDL_LoadBMP("3.bmp");
    SDL_Surface* spritesheet_mario = SDL_LoadBMP("mario.bmp");
    SDL_Surface* spritesheet_beczki = SDL_LoadBMP("4.bmp");

    char tekst[128];
    int czarny = SDL_MapRGB(ekran->format, 0x00, 0x00, 0x00);
    int kolorZielony = SDL_MapRGB(ekran->format, 0x00, 0xFF, 0x00);
    int kolorCzerwony = SDL_MapRGB(ekran->format, 0xFF, 0x00, 0x00);
    int niebieski = SDL_MapRGB(ekran->format, 0x11, 0x11, 0xCC);

    t1 = SDL_GetTicks();

    frames = 0;
    fpsTimer = 0;
    fps = 0;
    czyZakonczycGre = 0;
    distance = 0;
    etiSpeed = 1;

    Mario mario;
    InicjalizujGraczaMario(&mario);
    menu.czyMenuJestAktywne = 1;
    stanGry = STAN_GRY_MENU;
    ZainicjujEtap01(&platformy, &drabiny, &beczki);

    const int TARGET_FRAME_DURATION = 1000 / 60;

    while (!czyZakonczycGre) {
        int frameStartTime = SDL_GetTicks();

        t2 = SDL_GetTicks();

        delta = (t2 - t1) * 0.001;
        t1 = t2;
        if (!menu.czyMenuJestAktywne && stanGry != STAN_GRY_ZAPYTANIE_KONTYNUACJI &&
            stanGry != STAN_GRY_WYGRANA)
            mario.czasGry += delta;

        SDL_FillRect(ekran, NULL, czarny);

        fpsTimer += delta;
        if (fpsTimer > 0.5) {
            fps = frames * 2;
            frames = 0;
            fpsTimer -= 0.5;
        };
        int frameTime = SDL_GetTicks() - frameStartTime;
        if (frameTime < TARGET_FRAME_DURATION) {
            SDL_Delay(TARGET_FRAME_DURATION - frameTime);
        }

        RysujProstokat(ekran, 4, 4, SZEROKOSC_EKRANU - 8, 36, kolorCzerwony, niebieski);

        SDL_FillRect(ekran, NULL, czarny);

        if (menu.czyMenuJestAktywne == 1) {
            NarysujMenuUzytkownika(ekran, zestawZnakow);
        }
        else if (menu.czyMenuJestAktywne == 2) {
            NarysujMenuEtapy(ekran, zestawZnakow);
        }
        else if (menu.czyMenuJestAktywne == 3) {
            WypiszBrakImplementacji(ekran, zestawZnakow);
        }
        else {
            if (stanGry == STAN_GRY_GRA) {
                AktualizujGre(&mario, delta);

                for (int i = 0; i < mario.liczbaZyc; i++) {
                    RysujObrazSerduszka(ekran, obrazekZycia, 110 + i * 20, 28);
                }

                AktualizujPozycjeBeczek(beczki, iloscBeczek, delta);
                RysujBeczki(ekran, spritesheet_beczki, beczki, iloscBeczek);
                RysujPlatformy(ekran, spritesheet_platformy, platformy, iloscPlatform);
                WyswietlCzasGry(ekran, mario.czasGry, zestawZnakow);
                WyswietlNapisLiczbeZyc(ekran, zestawZnakow);
                RysujElementZakonczeniaEtapuETI(ekran, elementZakonczeniaGryETI);

                for (int i = 0; i < iloscDrabin; i++) {
                    RysujDrabine(ekran, drabina_spritesheet, &drabiny[i]);
                }

                RysujPostacMario(ekran, spritesheet_mario, &mario);
            }
            else if (stanGry == STAN_GRY_ZAPYTANIE_KONTYNUACJI) {
                char timeText[50];
                NarysujKolorowyNapis(ekran, 100, 130, "GRACZ O NICKU: ", zestawZnakow,
                    kolorZolty);

                NarysujKolorowyNapis(ekran, 220, 130, pseudonimGracza, zestawZnakow, kolorZolty);

                sprintf(timeText, "Czas gry: %.1lf s", mario.czasGry);
                NarysujKolorowyNapis(
                    ekran, 100, 150,
                    "CZY KONTYNUOWAC GRE? (K/M), 'K' - KONTYNUUJ, 'M' - MENU",
                    zestawZnakow, kolorCzerwony);
                NarysujKolorowyNapis(ekran, 100, 170, timeText, zestawZnakow, kolorZielony);

            }
            else if (stanGry == STAN_GRY_WYGRANA) {
                char timeText[50];
                sprintf(timeText, "Czas gry: %.1lf s", mario.czasGry);
                NarysujKolorowyNapis(ekran, 100, 150,
                    "WYGRALES, NACISNIJ 'M' ABY PRZEJSC DO MENU",
                    zestawZnakow, kolorCzerwony);
                NarysujKolorowyNapis(ekran, 100, 170, timeText, zestawZnakow, kolorZielony);
            }
        }
        SDL_UpdateTexture(scrtex, NULL, ekran->pixels, ekran->pitch);

        SDL_RenderCopy(renderer, scrtex, NULL, NULL);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (menu.czyMenuJestAktywne) {
                ObslugujZdarzenieMenu(&event, &menu, &czyZakonczycGre, &mario);
            }
            else {
                ObslugujKlawiature(&event, &mario, &czyZakonczycGre, &mario.czasGry);
            }
        };
        frames++;
    };

    delete[] platformy;
    delete[] drabiny;
    delete[] beczki;

    SDL_FreeSurface(zestawZnakow);
    SDL_FreeSurface(ekran);
    SDL_DestroyTexture(scrtex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(okno);

    SDL_Quit();
    return 0;
};