package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class Main {
    public static void main(String[] args) {
        Punkt punkt1 = new Punkt(3, 4);
        Punkt punkt2 = new Punkt(3, 4);

        System.out.println("Punkt 1: " + punkt1);
        System.out.println("Punkt 2: " + punkt2);
        System.out.println("Czy punkt1 == punkt2? " + (punkt1 == punkt2));
        System.out.println("Czy punkt1.equals(punkt2)? " + punkt1.equals(punkt2));
        System.out.println("Hashcode punkt1: " + punkt1.hashCode());
        System.out.println("Hashcode punkt2: " + punkt2.hashCode());

        System.out.println("Punkt O: " + Punkt.O);
        System.out.println("Punkt E_X: " + Punkt.E_X);
        System.out.println("Punkt E_Y: " + Punkt.E_Y);
    }
}
