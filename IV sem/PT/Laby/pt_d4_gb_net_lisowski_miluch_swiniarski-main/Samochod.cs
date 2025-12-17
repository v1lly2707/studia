using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace WpfApp1 
{
    public enum Nadwozie
    {
        Sedan,
        SUV,
        Cabrio,
    }


    public class Samochod : IComparable<Samochod>
    {

        public Czlowiek wlascicel { get; set; }
        public int liczbaDrzwi { get; set; } 

        public string marka { get; set; }

        public int CompareTo(Samochod other)
        {
            return this.liczbaDrzwi.CompareTo(other.liczbaDrzwi);
        }

        [XmlIgnore]
        public int ID { get; set; }

        public double PojemnoscSilnika { get; set; }

        public Nadwozie Nadwozie { get; set; }
    }

}
