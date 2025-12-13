package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class Schronisko extends Atrakcja {
    private String miejscowosc;
    public Schronisko(String m)
    {
        miejscowosc = m;
    }

    @Override
    public double getCzasZwiedzaniaAtrakcji()
    {
        return 0.4;

    }

    @Override
    public String getNazwa()
    {
        return "Schronisko";
    }
}
