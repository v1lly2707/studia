package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.PrzeprawaPrzezRzeke;


public class BagiennyBiegacz extends Czlowiek
{
    public BagiennyBiegacz(String imie, String nazwisko, Plec plec)
    {
        super(imie, nazwisko, plec, 8.0, 15.0, 19.7);
    }

    @Override
    public int getUmiejetnosciNawigacyjne()
    {
        return 5;
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas)
    {
        if(w instanceof PrzeprawaPrzezRzeke)
        {
            mow("Szybko się poruszam i dobrze nawiguję");
            aktualizujZmeczenie(czas/2);
        }
        else
        {
            super.reagujNaWedrowke(w, czas);
        }
    }

}