USE biuro_nieruchomosci
CREATE TABLE #Mieszkania_Staging (
    ID_mieszkania VARCHAR(10),
    Miasto VARCHAR(100), 
    Ulica VARCHAR(100), 
    Numer_budynku VARCHAR(10), 
    Numer_mieszkania VARCHAR(10), 
    Pietro INT, 
    Liczba_pokoi INT, 
    Wielkosc_mieszkania DECIMAL(10,2), 
    Cena INT, 
    Lata_budowy INT, 
    Miejsce_parkingowe INT, 
    Komorka_lokatorska INT, 
    Stan_mieszkania VARCHAR(50), 
    Balkon INT,
	Status_oferty VARCHAR(100),
	Opis VARCHAR(200)
);

BULK INSERT #Mieszkania_Staging
FROM 'C:\dane\Mieszkania.csv'
WITH (
    FIELDTERMINATOR = ';',
    ROWTERMINATOR = '\n',
    FIRSTROW = 2,
    CODEPAGE = '65001'
);

INSERT INTO dbo.Prezentacje (
    ID_mieszkania,
    ID_spotkania,
    ID_junk,
    Czas_trwania
)
SELECT 
    M.ID_mieszkania,
    S.ID_spotkania,       
    J.ID_junk,      
    DATEDIFF(minute, P.Godzina_rozpoczecia, P.Godzina_zakonczenia) AS Czas_trwania
FROM BiuroNieruchomoœci_Source.dbo.Prezentacje P
JOIN #Mieszkania_Staging MS 
    ON P.ID_mieszkania = MS.ID_mieszkania
JOIN BiuroNieruchomoœci_Source.dbo.Spotkania OS
    ON P.ID_spotkania = OS.ID_spotkania
JOIN dbo.Mieszkania M
    ON MS.Numer_budynku = M.Numer_budynku
   AND MS.Ulica = M.Ulica
   AND MS.Numer_mieszkania = M.Numer_mieszkania

JOIN dbo.Spotkania S
    ON S.ID_daty = (SELECT ID_daty 
                    FROM dbo.Data D
                    WHERE D.Rok = YEAR(OS.Data_spotkania)
                      AND D.Miesiac = MONTH(OS.Data_spotkania)
                      AND D.Dzien = DAY(OS.Data_spotkania))
   AND S.ID_klienta = (SELECT K.ID_klienta 
                       FROM dbo.Klienci K
                       WHERE K.PESEL = OS.PESEL_klienta)
   AND S.ID_agenta = (SELECT A.SK_agenta
                      FROM dbo.Agenci A
                      WHERE A.PESEL = OS.PESEL_agenta
                        AND A.Czy_aktualne = 1)

JOIN dbo.Junk J
    ON J.Decyzja_klienta = P.Decyzja_klienta

WHERE NOT EXISTS (
    SELECT 1
    FROM dbo.Prezentacje H
    WHERE H.ID_mieszkania = M.ID_mieszkania
      AND H.ID_spotkania = S.ID_spotkania
);

DROP TABLE #Mieszkania_Staging;