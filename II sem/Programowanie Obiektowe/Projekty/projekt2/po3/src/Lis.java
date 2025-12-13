import java.util.Random;

public class Lis extends Zwierze {
    public Lis(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat)
    {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public Lis(Organizm organizm) {
        super(organizm);
    }

    public void poruszanie() {
        int x_delta = 0;
        int y_delta = 0;
        Random random = new Random();
        int random_int = random.nextInt(9);
        switch (random_int) {
            case 0:
                x_delta += -1;
                y_delta += -1;
                break;
            case 1:
                y_delta += -1;
                break;
            case 2:
                x_delta += 1;
                y_delta += -1;
                break;
            case 3:
                x_delta += -1;
                break;
            case 4:
                x_delta += 1;
                break;
            case 5:
                y_delta += 1;
                x_delta += -1;
                break;
            case 6:
                x_delta += 1;
                break;
            case 7:
                y_delta += 1;
                x_delta += 1;
                break;
        }
        if (this.x_pos == 0 && x_delta == -1) {x_delta = 0;}
        if (this.y_pos == 0 && y_delta == -1) {y_delta = 0;}
        if (this.x_pos == this.swiat.getSzerokoscSwiata() - 1 && x_delta == 1) {x_delta = 0;}
        if (this.y_pos == this.swiat.getWysokoscSwiata() - 1 && y_delta == 1) {y_delta = 0;}


        Organizm organism = swiat.getOrganizm(x_pos + x_delta, y_pos + y_delta);
        if (organism != null && organism != this) {
            if (organism.sila < this.sila) {
                kolizja(organism);
            }
        } else {
            System.out.println("Nie znaleziono");
            x_pos += x_delta;
            y_pos += y_delta;
        }
        System.out.println(this.x_pos + " " + this.y_pos);
    }

    @Override
    Organizm kopiuj(Organizm organizm)
    {
        return new Lis(organizm);
    }

}
