INSERT INTO OddzialFirmy (KodPocztowy, Miasto, Ulica) VALUES
('00-001', 'Warszawa', 'Marszałkowska 10'),
('30-002', 'Kraków', 'Floriańska 5'),
('50-003', 'Wrocław', 'Świdnicka 15'),
('80-004', 'Gdańsk', 'Długa 25'),
('90-005', 'Łódź', 'Piotrkowska 12'),
('60-006', 'Poznań', 'Półwiejska 8'),
('20-007', 'Lublin', 'Krakowskie Przedmieście 3'),
('40-008', 'Katowice', 'Stawowa 18'),
('70-009', 'Szczecin', 'Wojska Polskiego 7'),
('15-010', 'Białystok', 'Lipowa 14'),
('35-011', 'Rzeszów', '3 Maja 20'),
('85-012', 'Bydgoszcz', 'Gdańska 30'),
('75-013', 'Kielce', 'Sienkiewicza 22'),
('65-014', 'Zielona Góra', 'Kupiecka 10'),
('95-015', 'Toruń', 'Szeroka 12'),
('55-016', 'Olsztyn', 'Stare Miasto 2'),
('45-017', 'Opole', 'Rynek 9'),
('25-018', 'Radom', 'Żeromskiego 17'),
('10-019', 'Sopot', 'Monte Cassino 4'),
('85-020', 'Gdynia', 'Świętojańska 11');

INSERT INTO AgentNieruchomosci (Pesel, Plec, Imie, Nazwisko, PracujeOd, KodPocztowy) VALUES
('90010112345', 'M', 'Jan', 'Kowalski', '2015-06-01', '00-001'),
('81020356789', 'K', 'Anna', 'Nowak', '2012-04-15', '30-002'),
('92040523456', 'M', 'Piotr', 'Wiśniewski', '2018-09-12', '50-003'),
('85050634567', 'K', 'Ewa', 'Kamińska', '2010-11-23', '80-004'),
('89070845678', 'M', 'Tomasz', 'Lewandowski', '2013-02-18', '90-005'),
('96080956789', 'K', 'Katarzyna', 'Wójcik', '2019-07-08', '60-006'),
('70091067890', 'M', 'Andrzej', 'Kaczmarek', '2005-03-15', '20-007'),
('75010178901', 'K', 'Magdalena', 'Zielińska', '2009-08-25', '40-008'),
('88020289012', 'M', 'Marek', 'Szymański', '2014-01-10', '70-009'),
('92030390123', 'K', 'Agnieszka', 'Woźniak', '2017-05-20', '15-010'),
('91040401234', 'M', 'Robert', 'Dąbrowski', '2016-06-15', '35-011'),
('87050512345', 'K', 'Joanna', 'Kwiatkowska', '2011-09-30', '85-012'),
('93060623456', 'M', 'Grzegorz', 'Pawlak', '2013-12-05', '75-013'),
('86070734567', 'K', 'Monika', 'Mazur', '2010-03-22', '65-014'),
('95080845678', 'M', 'Michał', 'Kozłowski', '2018-04-18', '95-015'),
('94090956789', 'K', 'Aleksandra', 'Piotrowska', '2019-02-25', '55-016'),
('89010167890', 'M', 'Adam', 'Zając', '2014-07-12', '45-017'),
('88020278901', 'K', 'Dorota', 'Górska', '2013-06-09', '25-018'),
('90030389012', 'M', 'Łukasz', 'Król', '2015-09-01', '10-019'),
('86040490123', 'K', 'Beata', 'Lis', '2008-11-17', '85-020');

INSERT INTO Kupujacy (Pesel, Imie, Nazwisko, WspolpracujeOd, Miejscowosc, PrzyblizonyBudzet, PeselAgenta) VALUES
('92010112345', 'Karol', 'Wiśniewski', '2019-01-12', 'Warszawa', 500000, '90010112345'),
('85020356789', 'Maria', 'Nowicka', '2018-06-25', 'Kraków', 800000, '81020356789'),
('90040523456', 'Mateusz', 'Lewicki', '2020-02-18', 'Wrocław', 600000, '92040523456'),
('87050634567', 'Zofia', 'Kamińska', '2017-10-30', 'Gdańsk', 700000, '85050634567'),
('89070845679', 'Paweł', 'Lis', '2016-03-11', 'Łódź', 450000, '89070845678'),
('96080956780', 'Patryk', 'Nowak', '2020-05-21', 'Poznań', 850000, '96080956789'),
('70091067891', 'Olga', 'Kaczmarek', '2019-09-14', 'Lublin', 300000, '70091067890'),
('75010178902', 'Barbara', 'Zielińska', '2018-04-01', 'Katowice', 950000, '75010178901'),
('88020289013', 'Damian', 'Szymański', '2021-03-19', 'Szczecin', 400000, '88020289012'),
('92030390124', 'Julia', 'Kowal', '2015-07-28', 'Białystok', 700000, '92030390123'),
('91040401235', 'Marta', 'Wróbel', '2016-09-10', 'Rzeszów', 500000, '91040401234'),
('87050512346', 'Tomasz', 'Kwiatkowski', '2022-01-15', 'Bydgoszcz', 850000, '87050512345'),
('93060623457', 'Natalia', 'Pawlak', '2020-08-10', 'Kielce', 300000, '93060623456'),
('86070734568', 'Piotr', 'Mazur', '2021-10-05', 'Zielona Góra', 900000, '86070734567'),
('95080845679', 'Janina', 'Kozłowska', '2018-02-12', 'Toruń', 750000, '95080845678'),
('94090956780', 'Jacek', 'Piotrowski', '2022-03-28', 'Olsztyn', 600000, '94090956789'),
('89010167891', 'Aneta', 'Zając', '2021-06-14', 'Opole', 650000, '89010167890'),
('88020278902', 'Klaudia', 'Górska', '2022-05-09', 'Radom', 400000, '88020278901'),
('90030389013', 'Szymon', 'Król', '2020-04-15', 'Sopot', 700000, '90030389012'),
('86040490124', 'Anna', 'Lis', '2019-08-23', 'Gdynia', 850000, '86040490123');

INSERT INTO Sprzedajacy (Pesel, Imie, Nazwisko, WspolpracujeOd) VALUES
('80010112345', 'Wojciech', 'Kowalski', '2015-01-10'),
('87020356789', 'Grażyna', 'Nowak', '2016-03-25'),
('90040523456', 'Andrzej', 'Wiśniewski', '2017-06-12'),
('85050634567', 'Bożena', 'Kamińska', '2018-09-05'),
('89070845679', 'Stanisław', 'Lewandowski', '2019-04-15'),
('96080956780', 'Magdalena', 'Wójcik', '2020-02-20'),
('70091067891', 'Leszek', 'Kaczmarek', '2019-11-30'),
('75010178902', 'Barbara', 'Zielińska', '2017-08-09'),
('88020289013', 'Paweł', 'Szymański', '2018-10-12'),
('92030390124', 'Katarzyna', 'Woźniak', '2019-06-25'),
('91040401235', 'Jan', 'Dąbrowski', '2020-07-18'),
('87050512346', 'Joanna', 'Kwiatkowska', '2016-12-01'),
('93060623457', 'Mariusz', 'Pawlak', '2018-01-14'),
('86070734568', 'Monika', 'Mazur', '2021-02-23'),
('95080845679', 'Krzysztof', 'Kozłowski', '2022-05-10'),
('94090956780', 'Anna', 'Piotrowska', '2020-03-12'),
('89010167891', 'Michał', 'Zając', '2017-11-08'),
('88020278902', 'Dorota', 'Górska', '2018-09-21'),
('90030389013', 'Łukasz', 'Król', '2019-10-15'),
('86040490124', 'Beata', 'Lis', '2021-08-19');

INSERT INTO Nieruchomosc (IdNieruchomosci, CzySprzedana, ProponowanaCena, Wojewodztwo, Miasto, Dzielnica, Ulica, RodzajNieruchomosci, PowierzchniaNieruchomosci, LiczbaPokoi, Rynek, PeselKupujacego, PeselSprzedajacego) VALUES
(1, 1, 600000, 'Mazowieckie', 'Warszawa', 'Centrum', 'Marszałkowska 10', 'Mieszkanie', 65, 3, 'Wtorny', '92010112345', '80010112345'),
(2, 0, 750000, 'Małopolskie', 'Kraków', 'Kazimierz', 'Floriańska 5', 'Mieszkanie', 80, 4, 'Pierwotny', '85020356789', '87020356789'),
(3, 1, 500000, 'Dolnośląskie', 'Wrocław', 'Śródmieście', 'Świdnicka 15', 'Mieszkanie', 55, 2, 'Wtorny', '90040523456', '90040523456'),
(4, 0, 1200000, 'Pomorskie', 'Gdańsk', 'Oliwa', 'Długa 25', 'Dom', 120, 5, 'Pierwotny', '87050634567', '85050634567'),
(5, 1, 450000, 'Łódzkie', 'Łódź', 'Bałuty', 'Piotrkowska 12', 'Mieszkanie', 45, 2, 'Wtorny', '89070845679', '89070845679'),
(6, 0, 950000, 'Wielkopolskie', 'Poznań', 'Stare Miasto', 'Półwiejska 8', 'Dom', 100, 4, 'Pierwotny', '96080956780', '96080956780'),
(7, 1, 850000, 'Lubelskie', 'Lublin', 'Czuby', 'Krakowskie Przedmieście 3', 'Dom', 110, 5, 'Wtorny', '70091067891', '70091067891'),
(8, 1, 700000, 'Śląskie', 'Katowice', 'Koszutka', 'Stawowa 18', 'Mieszkanie', 75, 3, 'Pierwotny', '75010178902', '75010178902'),
(9, 0, 620000, 'Zachodniopomorskie', 'Szczecin', 'Pogodno', 'Wojska Polskiego 7', 'Mieszkanie', 70, 3, 'Wtorny', '88020289013', '88020289013'),
(10, 1, 900000, 'Podlaskie', 'Białystok', 'Bacieczki', 'Lipowa 14', 'Dom', 130, 6, 'Pierwotny', '92030390124', '92030390124');

INSERT INTO OfertaKupna (IdOferty, Cena, PeselKupujacego, IdNieruchomosci) VALUES
(1, 580000, '92010112345', 1),
(2, 740000, '85020356789', 2),
(3, 490000, '90040523456', 3),
(4, 1180000, '87050634567', 4),
(5, 430000, '89070845679', 5),
(6, 920000, '96080956780', 6),
(7, 830000, '70091067891', 7),
(8, 680000, '75010178902', 8),
(9, 600000, '88020289013', 9),
(10, 880000, '92030390124', 10);

INSERT INTO Sprzedaz (IdSprzedazy, OstatecznaCena, DataSprzedazy, PeselAgenta, PeselKupujacego, PeselSprzedajacego, IdNieruchomosci) VALUES
(1, 590000, '2023-01-10', '90010112345', '92010112345', '80010112345', 1),
(2, 720000, '2023-02-15', '81020356789', '85020356789', '87020356789', 2),
(3, 495000, '2023-03-20', '92040523456', '90040523456', '90040523456', 3),
(4, 1190000, '2023-04-12', '85050634567', '87050634567', '85050634567', 4),
(5, 440000, '2023-05-18', '89070845678', '89070845679', '89070845679', 5);

INSERT INTO Mieszkanie (IdNieruchomosci, Pietro, KomorkaLokatorska, MiejsceParkingowe) VALUES
(1, 3, 1, 0),
(2, 5, 0, 1),
(3, 2, 1, 1),
(5, 4, 0, 0),
(9, 1, 1, 1);

INSERT INTO Dom (IdNieruchomosci, LiczbaPieter, PowierzchniaDzialki) VALUES
(4, 2, 500),
(6, 1, 400),
(7, 3, 600),
(8, 2, 550),
(10, 2, 700);
