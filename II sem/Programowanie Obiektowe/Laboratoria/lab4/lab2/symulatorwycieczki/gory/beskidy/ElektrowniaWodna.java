package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class ElektrowniaWodna extends Atrakcja {

    public ElektrowniaWodna(String nazwaAtrakcji, String nazwaMiejscowosci)
    {
        setNazwaAtrakcji(nazwaAtrakcji);
        setNazwaMiejscowosci(nazwaMiejscowosci);
    }

    @Override
    public double getCzasZwiedzaniaAtrakcji()
    {
        return 0.57;
    }

    @Override
    public String getNazwa()
    {
        return getNazwaAtrakcji();
    }
}
