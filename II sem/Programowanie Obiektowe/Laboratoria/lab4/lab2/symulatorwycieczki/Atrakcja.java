package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

public abstract class Atrakcja implements ElementWycieczki {

    private double czasZwiedzaniaAtrakcji;
    private String nazwaAtrakcji;
    private String nazwaMiejscowosci;

    public double getCzasZwiedzaniaAtrakcji()
    {
        return czasZwiedzaniaAtrakcji;
    }

    public String getNazwaAtrakcji()
    {
        return nazwaAtrakcji;
    }

    public String getNazwaMiejscowosci()
    {
        return nazwaMiejscowosci;
    }


    public void setCzasZwiedzaniaAtrakcji(double czasZwiedzaniaAtrakcji)
    {
        this.czasZwiedzaniaAtrakcji = czasZwiedzaniaAtrakcji;
    }

    public void setNazwaAtrakcji(String nazwaAtrakcji)
    {
        this.nazwaAtrakcji = nazwaAtrakcji;
    }

    public void setNazwaMiejscowosci(String nazwaMiejscowosci)
    {
        this.nazwaMiejscowosci = nazwaMiejscowosci;
    }
}
