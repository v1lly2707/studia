package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;


public class Tory extends Wedrowka{

    public Tory(double odleglosc){
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc){
        return (predkosc * (0.96));
    }

    @Override
    public int getTrudnoscNawigacyjna(){
        return 1;
    }

    @Override
    public String getNazwa(){
        return "Tory kolejki wąskotorowej. Są mniej wygodne niż droga, ale pozwalają na łatwą nawigację.";
    }
}
