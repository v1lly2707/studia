package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class TransOX implements Transformacja
{

    public TransOX(){}


    @Override

    public Punkt transformuj(Punkt p)
    {
        return new Punkt(p.getX(),(-1)*p.getY());
    }

    @Override

    public Transformacja getTransformacjaOdwrotna()
    {
        return new TransOX();
    }

    public String toString() {
        return "Obrot wzgledem osi OX ";
    }
}
