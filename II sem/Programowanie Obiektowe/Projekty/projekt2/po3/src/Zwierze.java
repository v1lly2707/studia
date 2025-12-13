import java.util.Objects;
import java.util.Random;

public abstract class Zwierze extends Organizm {



    Zwierze(String ikonka, int x, int y, int sila, int inicjatywa, Swiat swiat) {
        super(ikonka, x, y, sila, inicjatywa, swiat);
        moc = false;
    }
    Zwierze(Organizm organizm) {
        super(organizm);
        moc = false;
    }
    public void akcja() {
        if (this.czyZyje) {
            poruszanie();
        }

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
            kolizja(organism);
        } else {
//            System.out.println("No organism found");
            x_pos += x_delta;
            y_pos += y_delta;
        }
        System.out.println(this.x_pos + " " + this.y_pos);
    }

    public void kolizja(Organizm organizm) {
        if (Objects.equals(organizm.ikonka, this.ikonka)) {
            super.rozmnazanie();
        } else {
            if (organizm.sila > this.sila) {
//                System.out.println(this.icon + " was killed");
                this.zabijanie();
            } else {
//                System.out.println(organism.icon + " was killed");
                if (organizm instanceof Roslina) {
                    ((Roslina) organizm).moc(this);
                }

                this.x_pos = organizm.x_pos;
                this.y_pos = organizm.y_pos;
                organizm.zabijanie();
            }
        }
    }









}
