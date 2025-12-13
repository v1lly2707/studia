package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.PrzeprawaPrzezRzeke;;

public class Informatyk extends Czlowiek{
    public Informatyk(String imie, String nazwisko, Plec plec)
    {
        super(imie, nazwisko, plec, 8.2, 4.4, 3.3);
    }

    @Override
    public int getUmiejetnosciNawigacyjne()
    {
        return 4;
    }

    @Override
    public void reagujNaWedrowke(Wedrowka a, double czas)
    {
        if(a instanceof PrzeprawaPrzezRzeke)
        {
            mow("Pomagam informatykowi");
            regeneruj(czas*2);
        }
        else
        {
            super.reagujNaWedrowke(a, czas);
        }
    }

}

