USE biuro_nieruchomosci
UPDATE H
SET H.Czy_aktualne = 0
FROM dbo.Agenci H
JOIN BiuroNieruchomoœci_Source.dbo.Agenci S ON H.PESEL = S.PESEL
WHERE H.Czy_aktualne = 1
AND (
    H.Imie_i_nazwisko <> (S.Imie + ' ' + S.Nazwisko) OR 
    H.Numer_telefonu <> S.Nr_telefonu OR  
    H.Adres_email <> S.Email OR   
    
    H.Staz <> 
    (
        CASE
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR 
                           (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE())))
                      THEN 1 ELSE 0 END BETWEEN 0 AND 2 THEN '0-2'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR 
                           (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE())))
                      THEN 1 ELSE 0 END BETWEEN 3 AND 5 THEN '3-5'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR 
                           (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE())))
                      THEN 1 ELSE 0 END BETWEEN 6 AND 10 THEN '6-10'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR 
                           (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE())))
                      THEN 1 ELSE 0 END > 10 THEN '10+'
            ELSE NULL 
        END
    ) OR
    
    H.Wiek <> 
    (
        CASE
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR 
                           (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE()))
                      THEN 1 ELSE 0 END BETWEEN 18 AND 26 THEN '18-26'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR 
                           (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE()))
                      THEN 1 ELSE 0 END BETWEEN 27 AND 35 THEN '27-35'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR 
                           (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE()))
                      THEN 1 ELSE 0 END BETWEEN 36 AND 45 THEN '36-45'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR 
                           (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE()))
                      THEN 1 ELSE 0 END BETWEEN 46 AND 55 THEN '46-55'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR 
                           (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE()))
                      THEN 1 ELSE 0 END BETWEEN 56 AND 65 THEN '56-65'
            WHEN DATEDIFF(year, S.Data_urodzenia, GETDATE()) -
                 CASE WHEN MONTH(S.Data_urodzenia) > MONTH(GETDATE()) OR 
                           (MONTH(S.Data_urodzenia) = MONTH(GETDATE()) AND DAY(S.Data_urodzenia) > DAY(GETDATE()))
                      THEN 1 ELSE 0 END > 65 THEN '65+'
            ELSE NULL 
        END
    )
);



INSERT INTO dbo.Agenci (ID_agenta, PESEL, Imie_i_nazwisko, Plec, Adres_email, Numer_telefonu, Wiek, Staz, Czy_aktualne)
SELECT 
    S.ID_agenta, 
    S.PESEL, 
    S.Imie + ' ' + S.Nazwisko AS Imie_i_nazwisko, 
    
    CASE S.Plec
        WHEN 'K' THEN 'kobieta'
        WHEN 'M' THEN 'mê¿czyzna'
        ELSE NULL 
    END AS Plec, 
    
    S.Email, 
    S.Nr_telefonu, 
    
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
    
    (
        CASE
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END BETWEEN 0 AND 2 THEN '0-2'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END BETWEEN 3 AND 5 THEN '3-5'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END BETWEEN 6 AND 10 THEN '6-10'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END > 10 THEN '10+'
            ELSE NULL
        END
    ) AS Staz,
    1 
FROM BiuroNieruchomoœci_Source.dbo.Agenci S
JOIN dbo.Agenci H ON S.PESEL = H.PESEL
WHERE H.Czy_aktualne = 0 
  AND NOT EXISTS (SELECT 1 FROM dbo.Agenci A WHERE A.PESEL = S.PESEL AND A.Czy_aktualne = 1);



INSERT INTO dbo.Agenci (ID_agenta, PESEL, Imie_i_nazwisko, Plec, Adres_email, Numer_telefonu, Wiek, Staz, Czy_aktualne)
SELECT 
    S.ID_agenta, 
    S.PESEL, 
    S.Imie + ' ' + S.Nazwisko AS Imie_i_nazwisko, 
    
    CASE S.Plec
        WHEN 'K' THEN 'kobieta'
        WHEN 'M' THEN 'mê¿czyzna'
        ELSE NULL 
    END AS Plec, 
    
    S.Email, 
    S.Nr_telefonu, 
    
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
    
    (
        CASE
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END BETWEEN 0 AND 2 THEN '0-2'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END BETWEEN 3 AND 5 THEN '3-5'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END BETWEEN 6 AND 10 THEN '6-10'
            WHEN DATEDIFF(year, S.Data_zatrudnienia, COALESCE(S.Data_zwolnienia, GETDATE())) -
                 CASE WHEN MONTH(S.Data_zatrudnienia) > MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) OR (MONTH(S.Data_zatrudnienia) = MONTH(COALESCE(S.Data_zwolnienia, GETDATE())) AND DAY(S.Data_zatrudnienia) > DAY(COALESCE(S.Data_zwolnienia, GETDATE()))) THEN 1 ELSE 0 END > 10 THEN '10+'
            ELSE NULL
        END
    ) AS Staz,
    1
FROM BiuroNieruchomoœci_Source.dbo.Agenci S
WHERE NOT EXISTS (SELECT 1 FROM dbo.Agenci H WHERE H.PESEL = S.PESEL);