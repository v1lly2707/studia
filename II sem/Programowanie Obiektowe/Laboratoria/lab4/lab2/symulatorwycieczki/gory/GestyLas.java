package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

public class GestyLas extends Wedrowka{

    public GestyLas(double odleglosc)
    {
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc)
    {
        return (predkosc * 0.39);
    }

    @Override
    public int getTrudnoscNawigacyjna()
    {
        return 6;
    }

    @Override
    public String getNazwa()
    {
        return "Przejście na przełaj przez gesty las w którym nawigacja jest trudniejsza niz w zwyklym lesie";
    }
}

