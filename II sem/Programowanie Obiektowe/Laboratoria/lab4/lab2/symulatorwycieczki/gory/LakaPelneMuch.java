package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;


public class LakaPelneMuch extends Wedrowka{

    public LakaPelneMuch(double odleglosc)
    {
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc)
    {
        return (predkosc * (1.25));
    }

    @Override
    public int getTrudnoscNawigacyjna()
    {
        return 1;
    }

    @Override
    public String getNazwa()
    {
        return "Łąka pełna gryzących much (Jusznic). Grupa porusza się szybko aby uniknąć pogryzień.";
    }
}

