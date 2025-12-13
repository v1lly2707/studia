CREATE TABLE OddzialFirmy (
    KodPocztowy CHAR(5) NOT NULL PRIMARY KEY,
    Miasto VARCHAR(25),
    Ulica VARCHAR(25)
);

CREATE TABLE AgentNieruchomosci (
    Pesel CHAR(11) NOT NULL PRIMARY KEY,
    Plec CHAR(1) NOT NULL CHECK (Plec IN ('M', 'K')),
    Imie VARCHAR(15),
    Nazwisko VARCHAR(20),
    PracujeOd DATE,
    KodPocztowy CHAR(5) REFERENCES OddzialFirmy(KodPocztowy)
);

CREATE TABLE Kupujacy (
    Pesel CHAR(11) NOT NULL PRIMARY KEY,
    Imie VARCHAR(15),
    Nazwisko VARCHAR(20),
    WspolpracujeOd DATE,
    Miejscowosc VARCHAR(25),
    PrzyblizonyBudzet BIGINT,
    PeselAgenta CHAR(11) REFERENCES AgentNieruchomosci(Pesel)
);

CREATE TABLE Sprzedajacy (
    Pesel CHAR(11) NOT NULL PRIMARY KEY,
    Imie VARCHAR(15),
    Nazwisko VARCHAR(20),
    WspolpracujeOd DATE
);

CREATE TABLE Nieruchomosc (
    IdNieruchomosci INT NOT NULL PRIMARY KEY,
    CzySprzedana BOOLEAN,
    ProponowanaCena BIGINT,
    Wojewodztwo VARCHAR(25),
    Miasto VARCHAR(25),
    Dzielnica VARCHAR(25),
    Ulica VARCHAR(25),
    RodzajNieruchomosci VARCHAR(15) NOT NULL CHECK (RodzajNieruchomosci IN ('Dom', 'Mieszkanie')),
    PowierzchniaNieruchomosci INT,
    LiczbaPokoi SMALLINT,
    Rynek VARCHAR(10) NOT NULL CHECK (Rynek IN ('Pierwotny', 'Wtorny')),
    PeselKupujacego CHAR(11) REFERENCES Kupujacy(Pesel),
    PeselSprzedajacego CHAR(11) REFERENCES Sprzedajacy(Pesel)
);

CREATE TABLE OfertaKupna (
    IdOferty SMALLINT NOT NULL PRIMARY KEY,
    Cena BIGINT,
    PeselKupujacego CHAR(11) REFERENCES Kupujacy(Pesel),
    IdNieruchomosci INT REFERENCES Nieruchomosc(IdNieruchomosci)
);

CREATE TABLE Sprzedaz (
    IdSprzedazy INT NOT NULL PRIMARY KEY,
    OstatecznaCena BIGINT,
    DataSprzedazy DATE,
    PeselAgenta CHAR(11) REFERENCES AgentNieruchomosci(Pesel),
    PeselKupujacego CHAR(11) REFERENCES Kupujacy(Pesel),
    PeselSprzedajacego CHAR(11) REFERENCES Sprzedajacy(Pesel),
    IdNieruchomosci INT REFERENCES Nieruchomosc(IdNieruchomosci)
);

CREATE TABLE Mieszkanie (
    IdNieruchomosci INT NOT NULL PRIMARY KEY REFERENCES Nieruchomosc(IdNieruchomosci),
    Pietro SMALLINT,
    KomorkaLokatorska BOOLEAN,
    MiejsceParkingowe BOOLEAN
);

CREATE TABLE Dom (
    IdNieruchomosci INT NOT NULL PRIMARY KEY REFERENCES Nieruchomosc(IdNieruchomosci),
    LiczbaPieter SMALLINT,
    PowierzchniaDzialki INT
);
