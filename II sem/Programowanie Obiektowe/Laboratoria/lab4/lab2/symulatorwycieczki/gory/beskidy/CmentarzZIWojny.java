package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class CmentarzZIWojny extends Atrakcja {
    private String miejscowosc;
    public CmentarzZIWojny(String m)
    {
        miejscowosc = m;
    }

    @Override
    public double getCzasZwiedzaniaAtrakcji()
    {
        return 0.33;

    }

    @Override
    public String getNazwa()
    {
        return getNazwaAtrakcji();
    }
}
