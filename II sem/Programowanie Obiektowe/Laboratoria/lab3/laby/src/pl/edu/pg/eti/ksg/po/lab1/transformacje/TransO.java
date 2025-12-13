package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class TransO implements Transformacja
{

    public TransO(){}


    @Override

    public Punkt transformuj(Punkt p)
    {
        return new Punkt((-1)*p.getX(),(-1)*p.getY());
    }

    @Override

    public Transformacja getTransformacjaOdwrotna()
    {
        return new TransO();
    }

    public String toString() {
        return "Obrot wzgledem punktu (0;0) ";
    }
}

