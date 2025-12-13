CREATE TABLE Agenci (
    SK_agenta BIGINT IDENTITY(1,1) PRIMARY KEY,
    ID_agenta VARCHAR(10),
    PESEL CHAR(11) NOT NULL,
    Imie_i_nazwisko VARCHAR(255),
    Plec VARCHAR(20) CHECK (Plec IN ('mê¿czyzna', 'kobieta')),
    Adres_email VARCHAR(255),
    Numer_telefonu VARCHAR(15),
    Wiek VARCHAR(10) CHECK (Wiek IN ('18-26', '27-35', '36-45', '46-55', '56-65', '65+')),
    Staz VARCHAR(10) CHECK (Staz IN ('0-2', '3-5', '6-10', '10+')),
    Czy_aktualne BIT NOT NULL DEFAULT 1
);

CREATE TABLE Klienci (
    ID_klienta BIGINT IDENTITY (1,1) PRIMARY KEY,
    PESEL CHAR(11) NOT NULL,
    Imie_i_nazwisko VARCHAR(255),
    Plec VARCHAR(20) CHECK (Plec IN ('mê¿czyzna', 'kobieta')),
    Wiek VARCHAR(10) CHECK (Wiek IN ('18-26', '27-35', '36-45', '46-55', '56-65', '65+')),
    Nr_telefonu VARCHAR(15),
    Adres_email VARCHAR(255),
    Preferowana_cena VARCHAR(30) CHECK (Preferowana_cena IN ('< 300 000', '300 000 - 600 000', '600 000 - 1 000 000', '1 000 000 - 1 500 000', '> 1 500 000')),
    Preferowana_lokalizacja VARCHAR(50) CHECK (Preferowana_lokalizacja IN ('Gdañsk', 'Gdynia', 'Sopot')),
    Preferowana_wielkosc_mieszkania VARCHAR(20) CHECK (Preferowana_wielkosc_mieszkania IN ('ma³e', 'œrednie', 'du¿e')),
    Preferowana_liczba_pokoi INT,
    Miejsce_parkingowe BIT,
    Komorka_lokatorska BIT,
    Preferowany_stan_mieszkania VARCHAR(20) CHECK (Preferowany_stan_mieszkania IN ('deweloperski', 'pod klucz', 'surowy')),
    Balkon BIT
);

CREATE TABLE Data (
    ID_daty BIGINT IDENTITY (1,1) PRIMARY KEY,
    Rok INT,
    Miesiac INT,
    Dzien INT,
    Dzien_tygodnia VARCHAR(20)
);

CREATE TABLE Mieszkania (
    ID_mieszkania BIGINT IDENTITY (1,1) PRIMARY KEY,
    Miasto VARCHAR(50) CHECK (Miasto IN ('Gdañsk', 'Gdynia', 'Sopot')),
    Ulica VARCHAR(255),
    Numer_budynku VARCHAR(4),
    Numer_mieszkania VARCHAR(4),
    Pietro INT,
    Liczba_pokoi INT,
    Wielkosc_mieszkania VARCHAR(20) CHECK (Wielkosc_mieszkania IN ('ma³e', 'œrednie', 'du¿e')),
    Cena VARCHAR(50) CHECK (Cena IN ('< 300 000', '300 000 - 600 000', '600 000 - 1 000 000', '1 000 000 - 1 500 000', '> 1 500 000')),
    Lata_budowy VARCHAR(50) CHECK (Lata_budowy IN('2018-2020','2021-2023', '2024-2025')),
    Miejsce_parkingowe BIT,
    Komorka_lokatorska BIT,
    Stan_mieszkania VARCHAR(20) CHECK (Stan_mieszkania IN ('deweloperski', 'pod klucz', 'surowy')),
    Balkon BIT,
);

CREATE TABLE Junk (
    ID_junk BIGINT IDENTITY (1,1) PRIMARY KEY,
    Decyzja_klienta VARCHAR(50),
    Ewentualny_powod_odmowy VARCHAR(255)
);

CREATE TABLE Spotkania (
    ID_spotkania BIGINT IDENTITY (1,1) PRIMARY KEY,
    ID_daty BIGINT FOREIGN KEY REFERENCES Data,
    ID_klienta BIGINT FOREIGN KEY REFERENCES Klienci,
    ID_agenta BIGINT FOREIGN KEY REFERENCES Agenci,
    Ocena_agenta DECIMAL(3,1),
);

CREATE TABLE Prezentacje (
    ID_mieszkania BIGINT FOREIGN KEY REFERENCES Mieszkania,
    ID_spotkania BIGINT FOREIGN KEY REFERENCES Spotkania,
    Czas_trwania INTEGER,
    ID_junk BIGINT FOREIGN KEY REFERENCES Junk,

    CONSTRAINT composite_pk PRIMARY KEY (
       ID_mieszkania,
       ID_spotkania,
       ID_junk
        )
);

