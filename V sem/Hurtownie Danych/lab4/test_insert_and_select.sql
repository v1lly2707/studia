INSERT INTO Agenci (ID_agenta, PESEL, Imie_i_nazwisko, Plec, Adres_email, Numer_telefonu, Wiek, Staz)
VALUES
(1001, '90010112345', 'Jan Kowalski', 'mê¿czyzna', 'jan.kowalski@agencja.pl', '500600700', '27-35', '3-5'),
(1002, '85031298765', 'Maria Nowak', 'kobieta', 'maria.nowak@agencja.pl', '511222333', '36-45', '6-10'),
(1003, '92050145678', 'Adam Wiœniewski', 'mê¿czyzna', 'adam.wisniewski@agencja.pl', '533444555', '18-26', '0-2');

INSERT INTO Klienci (PESEL, Imie_i_nazwisko, Plec, Wiek, Nr_telefonu, Adres_email,
                     Preferowana_cena, Preferowana_lokalizacja, Preferowana_wielkosc_mieszkania,
                     Preferowana_liczba_pokoi, Miejsce_parkingowe, Komorka_lokatorska,
                     Preferowany_stan_mieszkania, Balkon)
VALUES
('97010167890', 'Agnieszka Zaj¹c', 'kobieta', '27-35', '601700800', 'agnieszka@example.com',
 '< 300 000', 'Gdañsk', 'ma³e', 2, 1, 0, 'pod klucz', 1),
('88050511223', 'Piotr Lewandowski', 'mê¿czyzna', '36-45', '660550330', 'piotr@example.com',
 '300 000 - 600 000', 'Gdynia', 'œrednie', 3, 0, 1, 'deweloperski', 0),
('94030399887', 'Monika Krawczyk', 'kobieta', '27-35', '690880990', 'monika@example.com',
 '600 000 - 1 000 000', 'Sopot', 'du¿e', 4, 1, 1, 'pod klucz', 1);

INSERT INTO Data (Rok, Miesiac, Dzien, Dzien_tygodnia)
VALUES
(2025, 1, 10, 'Pi¹tek'),
(2025, 1, 11, 'Sobota'),
(2025, 1, 12, 'Niedziela');

INSERT INTO Mieszkania (
    Miasto, Ulica, Numer_budynku, Numer_mieszkania, Pietro, Liczba_pokoi,
    Wielkosc_mieszkania, Cena, Lata_budowy, Miejsce_parkingowe, Komorka_lokatorska,
    Stan_mieszkania, Balkon
)
VALUES
('Gdañsk', 'D³uga', '12', '5', 2, 2, 'ma³e', '< 300 000', '2018-2020', 1, 0, 'pod klucz', 1),
('Gdynia', 'Œwiêtojañska', '4', '12', 5, 3, 'œrednie', '300 000 - 600 000', '2021-2023', 0, 1, 'deweloperski', 0),
('Sopot', 'Monte Cassino', '8', '3', 1, 4, 'du¿e', '600 000 - 1 000 000', '2024-2025', 1, 1, 'pod klucz', 1);

INSERT INTO Junk (Decyzja_klienta, Ewentualny_powod_odmowy)
VALUES
('Kupi³', NULL),
('Odmówi³', 'Cena'),
('Odmówi³', 'Lokalizacja');

INSERT INTO Spotkania (ID_daty, ID_klienta, ID_agenta, Ocena_agenta)
VALUES
(1, 1, 1, 9.5),
(2, 2, 2, 8.0),
(3, 3, 3, 7.5);

INSERT INTO Prezentacje (ID_mieszkania, ID_spotkania, Czas_trwania, ID_junk)
VALUES
(1, 1, '45', 1),
(2, 2, '60', 2),
(3, 3, '55', 3);


SELECT * FROM Agenci;
SELECT * FROM Klienci;
SELECT * FROM Data;
SELECT * FROM Mieszkania;
SELECT * FROM Junk;
SELECT * FROM Spotkania;
SELECT * FROM Prezentacje;