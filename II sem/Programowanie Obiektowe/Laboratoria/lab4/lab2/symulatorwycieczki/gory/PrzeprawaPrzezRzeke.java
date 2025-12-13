package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

public class PrzeprawaPrzezRzeke extends Wedrowka{

    public PrzeprawaPrzezRzeke(double odleglosc)
    {
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc)
    {
        return (predkosc * 0.27);
    }

    @Override
    public int getTrudnoscNawigacyjna()
    {
        return 4;
    }

    @Override
    public String getNazwa()
    {
        return "Przejście przez większą rzekę wpoprzek lub wędrówka z biegiem rzeki";
    }
}

