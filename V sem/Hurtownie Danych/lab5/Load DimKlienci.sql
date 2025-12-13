UPDATE H
SET 
    H.Nr_telefonu = S.Nr_telefonu,       
    H.Adres_email = S.Email,       
    
    H.Preferowana_cena = 
    CASE 
        WHEN S.Dostepny_budzet < 300000 THEN '< 300 000'
        WHEN S.Dostepny_budzet BETWEEN 300000 AND 600000 THEN '300 000 - 600 000'
        WHEN S.Dostepny_budzet BETWEEN 600001 AND 1000000 THEN '600 000 - 1 000 000'
        WHEN S.Dostepny_budzet BETWEEN 1000001 AND 1500000 THEN '1 000 000 - 1 500 000'
        WHEN S.Dostepny_budzet > 1500000 THEN '> 1 500 000'
        ELSE NULL 
    END,
    
    H.Wiek =
    (
        CASE
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 18 AND 26 THEN '18-26'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 27 AND 35 THEN '27-35'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 36 AND 45 THEN '36-45'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 46 AND 55 THEN '46-55'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 56 AND 65 THEN '56-65'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END > 65 THEN '65+'
            ELSE NULL
        END
    )
FROM dbo.Klienci H
JOIN BiuroNieruchomoœci_Source.dbo.Klienci S 
    ON H.PESEL = S.PESEL
WHERE 
    H.Nr_telefonu <> S.Nr_telefonu OR 
    H.Adres_email <> S.Email OR 
    H.Preferowana_cena <> 
    CASE 
        WHEN S.Dostepny_budzet < 300000 THEN '< 300 000'
        WHEN S.Dostepny_budzet BETWEEN 300000 AND 600000 THEN '300 000 - 600 000'
        WHEN S.Dostepny_budzet BETWEEN 600001 AND 1000000 THEN '600 000 - 1 000 000'
        WHEN S.Dostepny_budzet BETWEEN 1000001 AND 1500000 THEN '1 000 000 - 1 500 000'
        WHEN S.Dostepny_budzet > 1500000 THEN '> 1 500 000'
        ELSE NULL 
    END
    OR
    H.Preferowana_wielkosc_mieszkania <> 
    CASE
        WHEN S.Preferowany_metraz <= 45 THEN 'ma³e'
        WHEN S.Preferowany_metraz <= 75 THEN 'œrednie'
        WHEN S.Preferowany_metraz > 75 THEN 'du¿e'
        ELSE NULL 
    END
    OR
    H.Wiek <> 
    (
        CASE
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 18 AND 26 THEN '18-26'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 27 AND 35 THEN '27-35'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 36 AND 45 THEN '36-45'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 46 AND 55 THEN '46-55'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 56 AND 65 THEN '56-65'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END > 65 THEN '65+'
            ELSE NULL
        END
    );

---


INSERT INTO dbo.Klienci (
    PESEL, Imie_i_nazwisko, Plec, Wiek, Nr_telefonu, Adres_email, 
    Preferowana_cena, Preferowana_lokalizacja, Preferowana_wielkosc_mieszkania, 
    Preferowana_liczba_pokoi, Miejsce_parkingowe, Komorka_lokatorska, 
    Preferowany_stan_mieszkania, Balkon
)
SELECT 
    S.PESEL, 
    S.Imie + ' ' + S.Nazwisko AS Imie_i_nazwisko,
    
    CASE S.Plec
        WHEN 'K' THEN 'kobieta'
        WHEN 'M' THEN 'mê¿czyzna'
        ELSE NULL
    END AS Plec, 
    
    (
        CASE
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 18 AND 26 THEN '18-26'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 27 AND 35 THEN '27-35'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 36 AND 45 THEN '36-45'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 46 AND 55 THEN '46-55'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END BETWEEN 56 AND 65 THEN '56-65'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE())) THEN 1 ELSE 0 END > 65 THEN '65+'
            ELSE NULL
        END
    ) AS Wiek,        
    
    S.Nr_telefonu,    
    S.Email,    
    
    CASE 
        WHEN S.Dostepny_budzet < 300000 THEN '< 300 000'
        WHEN S.Dostepny_budzet BETWEEN 300000 AND 600000 THEN '300 000 - 600 000'
        WHEN S.Dostepny_budzet BETWEEN 600001 AND 1000000 THEN '600 000 - 1 000 000'
        WHEN S.Dostepny_budzet BETWEEN 1000001 AND 1500000 THEN '1 000 000 - 1 500 000'
        WHEN S.Dostepny_budzet > 1500000 THEN '> 1 500 000'
        ELSE NULL
    END AS Preferowana_cena, 
    
    S.Preferowana_lokalizacja, 
    
    CASE
        WHEN S.Preferowany_metraz <= 45 THEN 'ma³e'
        WHEN S.Preferowany_metraz <= 75 THEN 'œrednie'
        WHEN S.Preferowany_metraz > 75 THEN 'du¿e'
        ELSE NULL 
    END AS Preferowana_wielkosc_mieszkania, 
    
    S.Preferowana_liczba_pokoi, 
    S.Miejsce_parkingowe, 
    S.Komorka_lokatorska,
    S.Preferowany_stan_mieszkania, 
    S.Balkon
FROM BiuroNieruchomoœci_Source.dbo.Klienci S
WHERE NOT EXISTS (
    SELECT 1 
    FROM dbo.Klienci H 
    WHERE H.PESEL = S.PESEL
);