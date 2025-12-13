public class Wilk extends Zwierze {
    public Wilk(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat)
    {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public Wilk(Organizm organizm)
    {
        super(organizm);
    }

    @Override
    public Organizm kopiuj(Organizm organizm) {
        return new Wilk(organizm);
    }

}
