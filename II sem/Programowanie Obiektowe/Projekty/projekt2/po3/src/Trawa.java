public class Trawa extends Roslina {

    public Trawa(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat) {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public Trawa(Organizm organizm) {

        super(organizm);
    }

    @Override
    void kolizja(Organizm organizm) {

    }

    @Override
    Organizm kopiuj(Organizm organizm) {
        return new Trawa(organizm);
    }

    @Override
    public void moc(Organizm organizm) {

    }
}
