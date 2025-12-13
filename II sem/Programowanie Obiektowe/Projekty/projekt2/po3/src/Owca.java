public class Owca extends Zwierze {
    public Owca(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat) {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public Owca(Organizm organizm) {
        super(organizm);
    }

    @Override
    Organizm kopiuj(Organizm organizm) {
        return new Owca(organizm);
    }


}
