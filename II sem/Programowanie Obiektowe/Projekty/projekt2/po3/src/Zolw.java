import java.util.Random;

public class Zolw extends Zwierze {
    public Zolw(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat) {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public Zolw(Organizm organism) {
        super(organism);
    }

    @Override
    public void poruszanie() {
        Random random = new Random();
        if (random.nextInt(5) == 1) {
            super.poruszanie();
        }
    }

    @Override
    Organizm kopiuj(Organizm organism) {
        return new Zolw(organism);
    }
}
