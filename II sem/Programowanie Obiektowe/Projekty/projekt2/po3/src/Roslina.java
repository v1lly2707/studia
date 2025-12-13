import java.util.Objects;
import java.util.Random;

public abstract class Roslina extends Organizm {

    double ratio = 0.25;

    public Roslina(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat) {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    public Roslina(Organizm organizm) {
        super(organizm);
    }




    @Override
    public void rozmnazanie() {
        Random rand = new Random();
        int rand_rate = rand.nextInt(100);
        if (rand_rate < ratio * 100) {
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


            Organizm organizm = swiat.getOrganizm(x_pos + x_delta, y_pos + y_delta);
            if (organizm != null && organizm != this) {
                //System.out.println("Taken");
                kolizja(organizm);
            } else {
                //System.out.println("Empty");
                Organizm o = kopiuj(this);
                o.x_pos += x_delta;
                o.y_pos += y_delta;
                swiat.nowe.add(o);
            }
        }


    }

    @Override
    void akcja() {
        if (this.czyZyje) {
            this.rozmnazanie();
        }

    }

    public abstract void moc(Organizm organizm);

    public void handle_collision(Organizm organizm) {
        if (Objects.equals(organizm.ikonka, this.ikonka)) {

        } else {
            if (organizm.sila > this.sila) {
//                System.out.println(this.icon + " was killed");
                this.zabijanie();
            } else {
//                System.out.println(organism.icon + " was killed");
                this.x_pos = organizm.x_pos;
                this.y_pos = organizm.y_pos;
                organizm.zabijanie();
            }
        }
    }

}
