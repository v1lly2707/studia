public abstract class Organizm
{
    String ikonka;
    int x_pos;
    int y_pos;
    int sila;
    int inicjatywa;
    Swiat swiat;

    public boolean czyZyje = true;
    public boolean moc;

    Organizm(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat)
    {
        this.ikonka = ikonka;
        this.x_pos = x_pos;
        this.y_pos = y_pos;
        this.sila = sila;
        this.inicjatywa = inicjatywa;
        this.swiat = swiat;
    }
    Organizm(Organizm organizm)
    {
        this.ikonka = organizm.ikonka;
        this.x_pos = organizm.x_pos;
        this.y_pos = organizm.y_pos;
        this.sila = organizm.sila;
        this.inicjatywa = organizm.inicjatywa;
        this.swiat = organizm.swiat;
    }
    abstract void akcja();

    abstract void kolizja(Organizm organizm);

    abstract Organizm kopiuj(Organizm organizm);

    protected void rysujOrganizm() {
        if (x_pos >= 0 && y_pos >= 0) {
            swiat.table.setValueAt(ikonka, x_pos, y_pos);
        }

    }

    public void rozmnazanie() {

        int new_delta_x = 0;
        int new_delta_y = 0;

        if (this.x_pos > this.swiat.getSzerokoscSwiata() / 2) {
            new_delta_x = -1;
        } else {
            new_delta_x = 1;
        }

        if (this.y_pos > this.swiat.getWysokoscSwiata() / 2) {
            new_delta_y = -1;
        } else {
            new_delta_y = 1;
        }


        Organizm organizm = kopiuj(this);
        organizm.x_pos = this.x_pos + new_delta_x;
        organizm.y_pos = this.y_pos + new_delta_y;

        this.swiat.nowe.add(organizm);


    }



    public void ustawSile(int sila) {
        this.sila = sila;
    }





    protected void zabijanie() {
        this.x_pos = -1;
        this.y_pos = -1;
        this.ikonka = " ";
        this.czyZyje = false;

    }
}
