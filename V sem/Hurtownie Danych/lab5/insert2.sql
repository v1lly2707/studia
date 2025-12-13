

INSERT INTO Spotkania (ID_daty, ID_klienta, ID_agenta, Ocena_agenta)
VALUES
--(1, 1, 1, 9.5),
(1, 2, 1, 5),
(1, 3, 2, 10)
--(2, 2, 2, 8.0),
--(3, 3, 3, 7.5)
;

INSERT INTO Prezentacje (ID_mieszkania, ID_spotkania, Czas_trwania, ID_junk)
VALUES
--(1, 1, '45', 1),
--(2, 2, '60', 2),
--(3, 3, '55', 3),
(2, 4, '30', 1),
(3, 5, '100', 1);