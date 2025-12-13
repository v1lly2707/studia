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


INSERT INTO dbo.Mieszkania (
    Miasto, Ulica, Numer_budynku, Numer_mieszkania, Pietro, 
    Liczba_pokoi, Wielkosc_mieszkania, Cena, Lata_budowy, 
    Miejsce_parkingowe, Komorka_lokatorska, Stan_mieszkania, Balkon
)
SELECT 
    S.Miasto, S.Ulica, 
    S.Numer_budynku, S.Numer_mieszkania, S.Pietro, 
    S.Liczba_pokoi, CASE
        WHEN S.Wielkosc_mieszkania <= 45 THEN 'ma³e'
        WHEN S.Wielkosc_mieszkania <= 75 THEN 'œrednie'
        WHEN S.Wielkosc_mieszkania > 75 THEN 'du¿e'
        ELSE NULL 
    END AS Wielkosc_mieszkania, 
	CASE 
        WHEN S.Cena < 300000 THEN '< 300 000'
        WHEN S.Cena BETWEEN 300000 AND 600000 THEN '300 000 - 600 000'
        WHEN S.Cena BETWEEN 600001 AND 1000000 THEN '600 000 - 1 000 000'
        WHEN S.Cena BETWEEN 1000001 AND 1500000 THEN '1 000 000 - 1 500 000'
        WHEN S.Cena > 1500000 THEN '> 1 500 000'
        ELSE NULL 
    END AS Cena,
    CASE
        WHEN S.Lata_budowy BETWEEN 2018 AND 2020 THEN '2018-2020'
        WHEN S.Lata_budowy BETWEEN 2021 AND 2023 THEN '2021-2023'
        WHEN S.Lata_budowy BETWEEN 2024 AND 2025 THEN '2024-2025'
        ELSE NULL 
    END AS Lata_budowy, S.Miejsce_parkingowe, S.Komorka_lokatorska, 
    S.Stan_mieszkania, S.Balkon
FROM #Mieszkania_Staging S 
WHERE NOT EXISTS (SELECT 1
    FROM dbo.Mieszkania H
    WHERE H.Numer_budynku = S.Numer_budynku
    AND H.Ulica = S.Ulica
      AND H.Numer_mieszkania = S.Numer_mieszkania);


DROP TABLE #Mieszkania_Staging;