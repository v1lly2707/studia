public class Guarana extends Roslina {

    public Guarana(String ikonka, int x_pos, int y_pos, int sila, int inicjatywa, Swiat swiat)
    {
        super(ikonka, x_pos, y_pos, sila, inicjatywa, swiat);

    }

    public Guarana(Organizm organizm)
    {

        super(organizm);

    }

    @Override
    void kolizja(Organizm organizm)
    {

    }

    public void moc(Organizm organizm)
    {
        organizm.ustawSile(organizm.sila += 5);
    }

    @Override
    Organizm kopiuj(Organizm organizm)
    {
        return new Guarana(organizm);
    }
}
