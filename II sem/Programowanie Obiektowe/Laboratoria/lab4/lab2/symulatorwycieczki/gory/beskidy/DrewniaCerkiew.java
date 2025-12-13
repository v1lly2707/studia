package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class DrewniaCerkiew extends Atrakcja {
    private String miejscowosc;
    public DrewniaCerkiew(String m)
    {
        miejscowosc = m;
    }

    @Override
    public double getCzasZwiedzaniaAtrakcji()
    {
        return 0.5;
    }

    @Override
    public String getNazwa()
    {
        return getNazwaAtrakcji();
    }
}