public class Czlowiek extends Zwierze{

    Czlowiek(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat) {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);
    }

    Czlowiek(Organizm organizm)
    {
        super(organizm);
    }

    @Override
    public void poruszanie()
    {
        System.out.println("Sila: " + sila);
        int x_delta = 0;
        int y_delta = 0;
        switch (this.swiat.getRuchCzlowieka())
        {
            case 0:
                x_delta = -1;
                break;
            case 1:
                x_delta = 1;
                break;
            case 2:
                y_delta = -1;
                break;
            case 3:
                y_delta = 1;
                break;
        }

        if (this.x_pos == 0 && x_delta == -1)
        {
            x_delta = 0;
        }
        if (this.y_pos == 0 && y_delta == -1)
        {
            y_delta = 0;
        }
        if (this.x_pos == this.swiat.getSzerokoscSwiata() - 1 && x_delta == 1)
        {
            x_delta = 0;
        }
        if (this.y_pos == this.swiat.getWysokoscSwiata() - 1 && y_delta == 1)
        {
            y_delta = 0;
        }

        Organizm organizm = swiat.getOrganizm(x_pos + x_delta, y_pos + y_delta);
        if (organizm != null && organizm != this)
        {
            super.kolizja(organizm);
        }
        else
        {

            x_pos += x_delta;
            y_pos += y_delta;
        }

    }

    @Override
    Organizm kopiuj(Organizm organizm)
    {
        return new Czlowiek(organizm);
    }
}
