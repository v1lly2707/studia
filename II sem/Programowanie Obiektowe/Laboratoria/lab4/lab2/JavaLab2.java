package pl.edu.pg.eti.ksg.po.lab2;

import java.util.HashSet;
import java.util.Set;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.*;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.*;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.LakaPelneMuch;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.DrewniaCerkiew;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.CmentarzZIWojny;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.*;

/**
 *
 * @author TB
 */
public class JavaLab2 {
    public static void main(String[] args) {
        Wycieczka w = doDydiowki();
        Set<SluchaczPostepow> listaSluchaczy = new HashSet<>();

        PrzewodnikStudencki przewodnik = new PrzewodnikStudencki("Stefan", "Długonogi", Czlowiek.Plec.MEZCZYZNA);
        Set<Uczestnik> uczestnicy = new HashSet<>();
        uczestnicy.add(new Hydrolog("Jacek", "Placek", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new LesnyBiegacz("Maria", "Kowalska", Czlowiek.Plec.KOBIETA));
        uczestnicy.add(new BagiennyBiegacz("Jan", "Nowak", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new CzlowiekZKontuzja("Maja", "Kowalczyk", Czlowiek.Plec.KOBIETA));
        uczestnicy.add(new Informatyk("Grzegorz", "Marcinkowski", Czlowiek.Plec.MEZCZYZNA));

        Grupa g = new Grupa(przewodnik, uczestnicy);
        SymulatorWycieczki symulator = new SymulatorWycieczki(g, w);

        listaSluchaczy.add((elementWycieczki, lp, liczbaElementow)->
        {
            if(lp == liczbaElementow) {
                System.out.println("Koniec wycieczki.");
            }
            else {
                System.out.println("Wycieczka trwa o liczbę liczbe "+lp+" / "+liczbaElementow+")");
            }
        });

        symulator.setListaSluchaczy((listaSluchaczy));
        symulator.symuluj();
    }


    public static Wycieczka doDydiowki() {
        Wycieczka ret = new Wycieczka("Do Dydiówki");
        ret.dodajElementWycieczki(new Droga(1.0));
        ret.dodajElementWycieczki(new DrewniaCerkiew("Smolnik"));
        ret.dodajElementWycieczki(new LakaPelneMuch(4.2));
        ret.dodajElementWycieczki(new CmentarzZIWojny("Najlepsza grupa"));
        ret.dodajElementWycieczki(new Droga(4.0));
        ret.dodajElementWycieczki(new PrzeprawaPrzezRzeke(4.0));
        ret.dodajElementWycieczki(new Las(2.0));
        ret.dodajElementWycieczki(new Tory(0.6));
        ret.dodajElementWycieczki(new Droga(5.0));
        ret.dodajElementWycieczki(new GestyLas(3.0));
        ret.dodajElementWycieczki(new Schronisko("Nazwa schroniska"));
        return ret;
    }

}
