public class BarszczSosnowskiego extends Roslina {
    public BarszczSosnowskiego(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat)
    {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public BarszczSosnowskiego(Organizm organizm)
    {
        super(organizm);
    }

    @Override
    void kolizja(Organizm organizm)
    {

    }

    @Override
    public void moc(Organizm organizm)
    {
        organizm.zabijanie();
    }

    @Override
    Organizm kopiuj(Organizm organizm)
    {
        return new BarszczSosnowskiego(organizm);
    }
}
