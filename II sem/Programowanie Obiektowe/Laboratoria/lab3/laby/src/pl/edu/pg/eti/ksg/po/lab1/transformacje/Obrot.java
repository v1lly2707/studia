package pl.edu.pg.eti.ksg.po.lab1.transformacje;
import java.lang.Math;
public class Obrot implements Transformacja{

    private final double angle;

    public Obrot(double angle)
    {
        this.angle = angle;
    }

    @Override


    public Transformacja getTransformacjaOdwrotna() throws
            BrakTransformacjiOdwrotnejException{

        return new Obrot (-angle);
    }

    @Override

    public Punkt transformuj(Punkt p)
    {
        return new Punkt (p.getX()*Math.cos(angle)-p.getY()*Math.sin(angle),p.getX()*Math.sin(angle)+p.getY()*Math.cos(angle));
    }
    public double getAngle()
    {
        return angle;
    }

    @Override

    public String toString() {
        return "Obrot "+angle;
    }

}
