package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class ZlozenieTransformacji implements Transformacja {

    private final Transformacja[] tab;

    public ZlozenieTransformacji(Transformacja[] tab) {
        this.tab = tab;
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() throws
            BrakTransformacjiOdwrotnejException {
        Transformacja[] tab1 = new Transformacja[tab.length];

        for(int i=tab.length-1;i>=0;i--)
        {
            tab1[tab.length-1-i]=tab[i].getTransformacjaOdwrotna();

        }

        return new ZlozenieTransformacji(tab1);

    }
    @Override
    public Punkt transformuj(Punkt p) {
        Punkt p1 = new Punkt(p.getX(),p.getY());

        for(Transformacja i:tab)
        {
            p1 = i.transformuj(p1);

        }
        return p1;
    }

    public Transformacja[] getTab()
    {
        return tab;
    }

    public String toString()
    {
        String n="";
        for(Transformacja i:tab)
        {
            n=n.concat(i.toString());
        }
        return n;
    }
}
