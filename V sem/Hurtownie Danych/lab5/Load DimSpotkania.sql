USE biuro_nieruchomosci
INSERT INTO dbo.Spotkania (
    ID_daty,
    ID_klienta,
    ID_agenta,
    Ocena_agenta
)
SELECT 
    D.ID_daty,
    K.ID_klienta,
    A.SK_agenta,
    S.Ocena_agenta
FROM BiuroNieruchomoœci_Source.dbo.Spotkania S

JOIN dbo.Data D 
  ON D.Rok = YEAR(S.Data_spotkania)
 AND D.Miesiac = MONTH(S.Data_spotkania)
 AND D.Dzien = DAY(S.Data_spotkania)

JOIN dbo.Klienci K 
    ON S.PESEL_klienta = K.PESEL 

JOIN dbo.Agenci A 
    ON S.PESEL_agenta = A.PESEL
   AND A.Czy_aktualne = 1

WHERE NOT EXISTS (
    SELECT 1 
    FROM dbo.Spotkania F
    WHERE F.ID_daty = D.ID_daty
      AND F.ID_klienta = K.ID_klienta
      AND F.ID_agenta = A.SK_agenta
      AND F.Ocena_agenta = S.Ocena_agenta
);