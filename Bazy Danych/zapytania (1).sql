--Podaj mi jednego agenta, kt�ry sprzeda� najwi�cej nieruchomo�ci b�d�cych domami
SELECT TOP 1 
    a.Pesel AS PeselAgenta,
    a.Imie,
    a.Nazwisko,
    COUNT(*) AS LiczbaSprzedanychDomow
FROM 
    Sprzedaz s
JOIN 
    Nieruchomosc n ON s.IdNieruchomosci = n.IdNieruchomosci
JOIN 
    Dom d ON n.IdNieruchomosci = d.IdNieruchomosci
JOIN 
    AgentNieruchomosci a ON s.PeselAgenta = a.Pesel
GROUP BY 
    a.Pesel, a.Imie, a.Nazwisko
ORDER BY 
    LiczbaSprzedanychDomow DESC;

-- Podaj mi oddzia� firmy, kt�rego suma cen sprzeda�y nieruchomo�ci przez agent�w wynosi najwi�cej w styczniu.

SELECT TOP 1
    o.KodPocztowy,
    o.Miasto,
    o.Ulica,
    SUM(s.OstatecznaCena) AS SumaSprzedazy
FROM 
    Sprzedaz s
JOIN 
    AgentNieruchomosci an ON s.PeselAgenta = an.Pesel
JOIN 
    OddzialFirmy o ON an.KodPocztowy = o.KodPocztowy
WHERE 
    MONTH(s.DataSprzedazy) = 1 
GROUP BY 
    o.KodPocztowy, o.Miasto, o.Ulica
ORDER BY 
    SumaSprzedazy DESC;

--Pan Andrzej jest zainteresowany kupnem mieszkania. Chce znale�� mieszkanie, kt�re mie�ci si� w bud�ecie do 700000, posiada 3 pokoje oraz miejsce parkingowe.

SELECT m.IdNieruchomosci
FROM Nieruchomosc n
JOIN Mieszkanie m ON n.IdNieruchomosci = m.IdNieruchomosci
WHERE n.ProponowanaCena < 700000
  AND n.LiczbaPokoi = 3
  AND m.MiejsceParkingowe = 1;


--Zestawienie agent�w nieruchomo�ci pracuj�cych w oddziale firmy znajduj�cych si� w Warszawie, uporz�dkowane wed�ug imienia i nazwiska.


SELECT 
    A.Pesel, 
    A.Imie, 
    A.Nazwisko, 
    A.PracujeOd, 
    O.Miasto, 
    O.Ulica
FROM 
    AgentNieruchomosci A
JOIN 
    OddzialFirmy O ON A.KodPocztowy = O.KodPocztowy
WHERE 
    O.Miasto = 'Warszawa'
ORDER BY 
    A.Nazwisko, A.Imie;


--Zliczenie ile nieruchomo�ci sprzeda� dany sprzedaj�cy o konkretnym numerze pesel.
SELECT COUNT(*) AS LiczbaSprzedanychNieruchomosci
FROM Sprzedaz S
JOIN Nieruchomosc N ON S.IdNieruchomosci = N.IdNieruchomosci
WHERE S.PeselSprzedajacego = '85050634567';

--Wyszukanie kupuj�cych kt�rzy nie posiadaj� �adnych nieruchomo�ci.

SELECT K.Pesel, K.Imie, K.Nazwisko
FROM Kupujacy K
WHERE NOT EXISTS (
    SELECT 1
    FROM Nieruchomosc N
    WHERE N.PeselKupujacego = K.Pesel
);

--. Ile nieruchomo�ci zosta�o sprzedanych w Gda�sku �r�dmie�cie w styczniu 2023?


SELECT COUNT(*) AS LiczbaSprzedazy
FROM Sprzedaz ok
JOIN Nieruchomosc n ON ok.IdNieruchomosci = n.IdNieruchomosci
WHERE n.Miasto = 'Gda�sk'
  AND n.Dzielnica = '�r�dmie�cie'
  AND n.RodzajNieruchomosci = 'Mieszkanie'
  AND MONTH(ok.DataSprzedazy) = 1
  AND YEAR(ok.DataSprzedazy) = 2023;

--Kt�ry klient posiada najwi�cej nieruchomosci w Gdansku?
SELECT TOP 1 
    s.Pesel AS PeselKlienta,
    s.Imie,
    s.Nazwisko,
    COUNT(n.IdNieruchomosci) AS LiczbaNieruchomosci
FROM 
    Sprzedajacy s
JOIN 
    Nieruchomosc n ON s.Pesel = n.PeselSprzedajacego
WHERE 
    n.Miasto = 'Gda�sk'
GROUP BY 
    s.Pesel, s.Imie, s.Nazwisko
ORDER BY 
    LiczbaNieruchomosci DESC;


--Kt�ry agent po�redniczy� w najwi�kszej liczbie sprzeda�y i jaka by�a ��czna kwota tych sprzeda�y?

SELECT TOP 1 
    a.Imie,
    a.Nazwisko,
    a.Pesel AS PeselAgenta,
    COUNT(s.IdSprzedazy) AS LiczbaSprzedazy,
    SUM(s.OstatecznaCena) AS LacznaKwotaSprzedazy
FROM 
    Sprzedaz s
INNER JOIN 
    AgentNieruchomosci a ON s.PeselAgenta = a.Pesel
GROUP BY 
    a.Imie, a.Nazwisko, a.Pesel
ORDER BY 
    LiczbaSprzedazy DESC, LacznaKwotaSprzedazy DESC;

