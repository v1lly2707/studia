package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Czlowiek;

public class CzlowiekZKontuzja extends Czlowiek {
    public CzlowiekZKontuzja(String imie, String nazwisko, Plec plec)
    {
        super(imie, nazwisko, plec, 1.5, 24.0, 5.0);
    }

    @Override
    public int getUmiejetnosciNawigacyjne()
    {
        return 2;
    }


}
