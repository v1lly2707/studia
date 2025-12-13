public class Antylopa extends Zwierze
{
    public Antylopa(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat)
    {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }
    public Antylopa(Organizm organizm)
    {
        super(organizm);
    }

    @Override
    public Organizm kopiuj(Organizm organizm)
    {
        return new Antylopa(organizm);
    }
}
