SET IDENTITY_INSERT Data ON;

SET LANGUAGE Polish;

DECLARE @StartDate DATE = '2020-01-01'; 
DECLARE @EndDate DATE = '2025-12-31';

WHILE @StartDate <= @EndDate
BEGIN
    DECLARE @DateKey INT = CAST(CONVERT(VARCHAR(8), @StartDate, 112) AS INT);

    IF NOT EXISTS (SELECT 1 FROM Data WHERE ID_daty = @DateKey)
    BEGIN
        INSERT INTO Data (
            ID_daty,
            Rok,
            Miesiac,
            Dzien,
            Dzien_tygodnia
        )
        VALUES (
            @DateKey,
            YEAR(@StartDate),
            MONTH(@StartDate),
            DAY(@StartDate),
            DATENAME(WEEKDAY, @StartDate)
        );
    END

    SET @StartDate = DATEADD(DAY, 1, @StartDate);
END

SET IDENTITY_INSERT Data OFF;

