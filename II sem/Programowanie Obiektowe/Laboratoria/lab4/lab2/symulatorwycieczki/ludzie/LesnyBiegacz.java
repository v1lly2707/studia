package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.CmentarzZIWojny;

public class LesnyBiegacz extends Czlowiek
{
    public LesnyBiegacz(String imie, String nazwisko, Plec plec)
    {
        super(imie, nazwisko, plec, 6.0, 14.0, 17.3);
    }

    @Override
    public int getUmiejetnosciNawigacyjne()
    {
        return 4;
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas)
    {
        if(a instanceof CmentarzZIWojny)
        {
            mow("Lubię cmentarze a zwłaszcza ze z I wojny światowej");
            regeneruj(czas*2);
        }
        else{
            super.reagujNaAtrakcje(a, czas);
        }
    }

}

