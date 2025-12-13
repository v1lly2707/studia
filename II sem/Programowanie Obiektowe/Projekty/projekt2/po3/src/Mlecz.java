public class Mlecz extends Roslina {
    public Mlecz(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat)
    {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public Mlecz(Organizm organizm)
    {
        super(organizm);
    }

    @Override
    void kolizja(Organizm organizm)
    {

    }

    @Override
    public void rozmnazanie()
    {
        super.rozmnazanie();
        super.rozmnazanie();
        super.rozmnazanie();
    }
    @Override
    public void moc(Organizm organizm)
    {

    }


    @Override
    Organizm kopiuj(Organizm organizm)
    {
        return new Trawa(organizm);
    }
}
