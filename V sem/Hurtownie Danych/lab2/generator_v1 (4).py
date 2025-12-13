import csv
from faker import Faker
import random
from datetime import datetime, timedelta

fake = Faker("pl_PL")


# -------------- MIESZKANIA ---------------------

n = 1000  # liczba mieszkań

stan_mieszkania = ["deweloperski", "pod klucz", "surowy"]
status_oferty = ["dostępne", "zarezerwowane", "sprzedane"]
miasto = ["Gdańsk", "Gdynia", "Sopot"]
opis_mieszkania = ["Ładne mieszkanie", "Spoko miejscówka", "Twoje nowe 4 kąty!", "Twój nowy dom"]

with open("Mieszkania.csv", "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file, delimiter=";")
    
    writer.writerow([
        "ID_mieszkania", "Miasto", "Ulica", "Numer_budynku", "Numer_mieszkania",
        "Pietro", "Liczba_pokoi", "Metraz", "Cena", "Rok_budowy",
        "Miejsce_parkingowe", "Komorka_lokatorska", "Stan_mieszkania",
        "Balkon", "Status_oferty", "Opis"
    ])
    
    for i in range(1, n + 1):
        writer.writerow([
            f"MW{i:05d}",                    # ID
            random.choice(miasto),           # Miasto        
            fake.street_name(),              # Ulica
            str(random.randint(1, 50)),      # Numer budynku
            str(random.randint(1, 200)),     # Numer mieszkania (opcjonalny)
            random.randint(0, 10),           # Piętro
            random.randint(1, 5),            # Liczba pokoi
            round(random.uniform(20.0, 150.0), 2),  # Metraż
            random.randint(150000, 1500000), # Cena
            random.randint(2023, 2025),      # Rok budowy
            random.choice(["TAK", "NIE"]),   # Miejsce parkingowe
            random.choice(["TAK", "NIE"]),   # Komórka lokatorska
            random.choice(stan_mieszkania),  # Stan mieszkania
            random.choice(["TAK", "NIE"]),   # Balkon
            random.choice(status_oferty),    # Status oferty
            random.choice(opis_mieszkania),  # Krótki opis
        ])

print(f"{n} mieszkań wygenerowano do pliku Mieszkania.csv")


# ----------------------- AGENCI ---------------------

n = 1000      # liczba agentów

def random_date(start_year=1960, end_year=2000):
    start = datetime(start_year, 1, 1)
    end = datetime(end_year, 12, 31)
    delta = end - start
    return start + timedelta(days=random.randint(0, delta.days))

def random_employment_date(birth_date):
    start = birth_date + timedelta(days=18*365)
    end = datetime.today()
    if start > end:
        start = end - timedelta(days=365)
    delta = end - start
    return start + timedelta(days=random.randint(0, delta.days))

def generate_pesel(birth_date):
    year = birth_date.year
    month = birth_date.month
    day = birth_date.day

    if 1900 <= year <= 1999:
        mm = month
    elif 2000 <= year <= 2099:
        mm = month + 20
    elif 1800 <= year <= 1899:
        mm = month + 80
    elif 2100 <= year <= 2199:
        mm = month + 40
    else:
        mm = month + 60  

    pesel_base = f"{year%100:02d}{mm:02d}{day:02d}"
    serial = f"{random.randint(0, 9999):04d}"
    pesel_without_checksum = pesel_base + serial

    weights = [1, 3, 7, 9, 1, 3, 7, 9, 1, 3]
    s = sum(int(pesel_without_checksum[i]) * weights[i] for i in range(10))
    checksum = (10 - s % 10) % 10

    return pesel_without_checksum + str(checksum)

with open("Agenci.csv", "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file, delimiter=";")
    writer.writerow([
        "ID_agenta", "PESEL", "Imie", "Nazwisko", "Plec", "Email",
        "Numer_telefonu", "Data_urodzenia", "Data_zatrudnienia", "Data_zwolnienia"
    ])
    
    for i in range(1, n + 1):
        birth_date = random_date()
        hire_date = random_employment_date(birth_date)

        # 20% agentów zostaje zwolnionych
        if random.random() < 0.2:
            fire_date = hire_date + timedelta(days=random.randint(30, 3650))
            fire_date = "" if fire_date > datetime.today() else fire_date.strftime("%Y-%m-%d")
        else:
            fire_date = ""

        # --- dopasowanie imienia do płci jak u klientów ---
        plec = random.choice(["M", "K"])
        first_name = fake.first_name_male() if plec == "M" else fake.first_name_female()

        writer.writerow([
            f"A{i:05d}",
            generate_pesel(birth_date),
            first_name,
            fake.last_name(),
            plec,
            fake.email(),
            fake.phone_number(),
            birth_date.strftime("%Y-%m-%d"),
            hire_date.strftime("%Y-%m-%d"),
            fire_date
        ])

print(f"{n} agentów wygenerowano do pliku Agenci.csv")

# --------------------- KLIENCI -------------------------


with open("Klienci.csv", "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file, delimiter=";")
    
    writer.writerow([
        "PESEL", "Imie", "Nazwisko", "Plec", "Data_urodzenia",
        "Nr_telefonu", "Email", "Dostepny_budzet", "Preferowana_lokalizacja",
        "Preferowany_metraz", "Preferowana_liczba_pokoi", "Miejsce_parkingowe",
        "Komorka_lokatorska", "Preferowany_stan_mieszkania", "Balkon"
    ])
    
    for _ in range(n):
        birth_date = random_date()
        sex = random.choice(["M", "K"])
        writer.writerow([
            generate_pesel(birth_date),
            fake.first_name_male() if sex=="M" else fake.first_name_female(),
            fake.last_name(),
            sex,
            birth_date.strftime("%Y-%m-%d"),
            fake.phone_number(),
            fake.email(),
            random.randint(100000, 2000000),   		  # dostępny budżet
            random.choice(miasto),                        # preferowana lokalizacja
            random.randint(20, 150),                      # preferowany metraż
            random.randint(1, 5),                         # preferowana liczba pokoi
            random.choice([True, False]),                 # miejsce parkingowe
            random.choice([True, False]),                 # komórka lokatorska
            random.choice(stan_mieszkania),              # preferowany stan mieszkania
            random.choice([True, False])                 # balkon
        ])

print(f"{n} klientów wygenerowano do pliku Klienci.csv")



# ------------------ SPOTKANIA ----------------------

def wczytaj_pesel_csv(file_name): # żeby korzystało z danych osób, które serio są w bazie
    pesel_list = []
    with open(file_name, newline='', encoding='utf-8') as file:
        reader = csv.DictReader(file, delimiter=';')
        for row in reader:
            pesel_list.append(row['PESEL'])
    return pesel_list

pesel_klienci = wczytaj_pesel_csv("Klienci.csv")
pesel_agenci = wczytaj_pesel_csv("Agenci.csv")

n = 5000  # liczba spotkań 

def random_meeting_date(start_date=None, end_date=None):
    if start_date is None:
        start_date = datetime.today()
    if end_date is None:
        end_date = start_date + timedelta(days=60)
    delta = end_date - start_date
    return start_date + timedelta(days=random.randint(0, delta.days))

with open("Spotkania.csv", "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file, delimiter=';')
    
    writer.writerow(["ID_spotkania", "Data_spotkania", "PESEL_klienta", "PESEL_agenta", "Ocena_agenta"])
    
    for i in range(1, n + 1):
        meeting_date = random_meeting_date().strftime("%d.%m.%Y")
        pesel_klient = random.choice(pesel_klienci)
        pesel_agent = random.choice(pesel_agenci)
        ocena = round(random.uniform(1, 10), 1)
        
        writer.writerow([
            i,  # ID spotkania
            meeting_date,
            pesel_klient,
            pesel_agent,
            ocena
        ])

print(f"{n} spotkań wygenerowano do pliku Spotkania.csv")



# ------------- PREZENTACJE ---------------------

def wczytaj_id_csv(file_name, id_field):
    id_list = []
    with open(file_name, newline='', encoding='utf-8') as file:
        reader = csv.DictReader(file, delimiter=';')
        for row in reader:
            id_list.append(row[id_field])
    return id_list

id_mieszkania = wczytaj_id_csv("Mieszkania.csv", "ID_mieszkania")
id_spotkania = wczytaj_id_csv("Spotkania.csv", "ID_spotkania")

n = 10000  # liczba prezentacji

decyzje_klienta = ["kupił", "zrezygnował", "zastanawia się"]
powody_odmowy = ["cena", "lokalizacja", "metraż", "brak finansowania", "inna oferta", "brak zainteresowania", "inne"]

def random_time(start_hour=9, end_hour=18):
    hour = random.randint(start_hour, end_hour-1)
    minute = random.choice([0, 15, 30, 45])
    return f"{hour:02d}:{minute:02d}"

with open("Prezentacje.csv", "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file, delimiter=';')
    
    writer.writerow([
        "ID_prezentacji", "ID_mieszkania", "ID_spotkania",
        "Godzina_rozpoczecia", "Godzina_zakonczenia",
        "Decyzja_klienta", "Powod_odmowy"
    ])
    
    for i in range(1, n + 1):
        mieszkanie_id = random.choice(id_mieszkania)
        spotkanie_id = random.choice(id_spotkania)
        
        start_time = random_time()
        start_hour, start_minute = map(int, start_time.split(":"))
        duration_minutes = random.choice(range(15, 91))
        end_datetime = datetime(2000,1,1,start_hour,start_minute) + timedelta(minutes=duration_minutes)
        end_time = end_datetime.strftime("%H:%M")
        
        decyzja = random.choice(decyzje_klienta)
        powod = random.choice(powody_odmowy) if decyzja == "odmowa" else ""
        
        writer.writerow([
            i,
            mieszkanie_id,
            spotkanie_id,
            start_time,
            end_time,
            decyzja,
            powod
        ])

print(f"{n} prezentacji wygenerowano do pliku Prezentacje.csv")
