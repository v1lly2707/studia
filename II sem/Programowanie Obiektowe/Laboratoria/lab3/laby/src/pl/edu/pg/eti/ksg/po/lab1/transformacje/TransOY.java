package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class TransOY implements Transformacja
{

    public TransOY(){}


    @Override

    public Punkt transformuj(Punkt p)
    {
        return new Punkt((-1)*p.getX(),p.getY());
    }

    @Override

    public Transformacja getTransformacjaOdwrotna()
    {
        return new TransOY();
    }

    public String toString() {
        return "Obrot wzgledem osi OY ";
    }
}
