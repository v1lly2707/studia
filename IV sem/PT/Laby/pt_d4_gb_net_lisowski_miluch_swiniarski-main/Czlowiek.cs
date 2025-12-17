using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Xml.Serialization;

namespace WpfApp1
{
    public class Czlowiek
    {
        private static readonly Random random = new Random();

        public int wzrost { get; set; }
        public int waga { get; set; }
        public string imie { get; set; }

        [XmlIgnore]
        public int ID { get; set; }

        public List<Czlowiek> Dzieci { get; set; } = new List<Czlowiek>();

        public Samochod Samochod { get; set; }

        private static Czlowiek createRandomCzlowiek(int glebokosc, int maxDzieci, Random random)
        {

            Czlowiek czlowiek = new Czlowiek
            {
                ID = random.Next(1, 100000000),
                imie = "Osoba" + random.Next(1, 1000),
                wzrost = random.Next(150, 200),
                waga = random.Next(50, 100)
            };

            czlowiek.Samochod = new Samochod
            {
                ID = random.Next(1, 100000),
                PojemnoscSilnika = random.Next(1, 5),
                Nadwozie = (Nadwozie)random.Next(0, 3),
                liczbaDrzwi = random.Next(2, 6),
                marka = Guid.NewGuid().ToString().Substring(0, 5)
            };

            if (glebokosc > 0)
            {
                int liczbaDzieci = random.Next(0, maxDzieci + 1);
                for (int i = 0; i < liczbaDzieci; i++)
                {
                    czlowiek.Dzieci.Add(createRandomCzlowiek(glebokosc - 1, maxDzieci, random));
                }
            }

            return czlowiek;
        }

        public static Czlowiek generateRandomCzlowiekData()
        {
            Czlowiek czlowiek = new Czlowiek
            {
                ID = random.Next(1, 100000000),
                imie = "Osoba" + random.Next(1, 1000),
                wzrost = random.Next(150, 200),
                waga = random.Next(50, 100)
            };

            czlowiek.Samochod = new Samochod
            {
                ID = random.Next(1, 100000),
                PojemnoscSilnika = random.Next(1, 5),
                Nadwozie = (Nadwozie)random.Next(0, 3),
                liczbaDrzwi = random.Next(2, 6),
                marka = Guid.NewGuid().ToString().Substring(0, 5)
            };

            return czlowiek;
        }

        public static List<Czlowiek> createRandomList(int glebokosc, int maxDzieci, int n)
        {
            List<Czlowiek> lista = new List<Czlowiek>();
            Random random = new Random();

            for (int i = 0; i < n; i++)
            {
                lista.Add(createRandomCzlowiek(glebokosc, maxDzieci, random));
            }

            return lista;
        }

        public String wypisz()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("\n");
            sb.AppendLine($"Imię: {imie}");
            sb.AppendLine($"Wzrost: {wzrost}");
            sb.AppendLine($"Waga: {waga}");
            sb.AppendLine($"ID: {ID}");
            sb.AppendLine($"Samochód: {Samochod?.ID}");

            switch (Samochod?.Nadwozie)
            {
                case Nadwozie.Sedan:
                    sb.AppendLine("Typ nadwozia: Sedan");
                    break;
                case Nadwozie.SUV:
                    sb.AppendLine("Typ nadwozia: SUV");
                    break;
                case Nadwozie.Cabrio:
                    sb.AppendLine("Typ nadwozia: Cabrio");
                    break;
            }

            sb.AppendLine($"Pojemność silnika: {Samochod?.PojemnoscSilnika}");
            sb.AppendLine($"Liczba drzwi: {Samochod?.liczbaDrzwi}");
            if (Dzieci != null && Dzieci.Count > 0)
            {
                sb.AppendLine("Dzieci:");
                foreach (var dziecko in Dzieci)
                {
                    sb.Append("    ");
                    sb.Append(dziecko.wypisz());
                }
            }
            return sb.ToString();
        }
    }

}