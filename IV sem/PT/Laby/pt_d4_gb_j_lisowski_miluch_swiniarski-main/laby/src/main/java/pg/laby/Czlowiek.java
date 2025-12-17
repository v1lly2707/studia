package pg.laby;

import java.io.Serializable;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;

public class Czlowiek implements Comparable<Czlowiek>, Comparator<Czlowiek>, Serializable {
    public int wzrost;
    public int waga;
    public String imie;
    Set<Czlowiek> dzieci;

    public Czlowiek(int wzrost, int waga, String imie, Set<Czlowiek> dzieci) {
        this.wzrost = wzrost;
        this.waga = waga;
        this.imie = imie;
        this.dzieci = dzieci;
    }

    public Czlowiek(int wzrost, int waga, String imie) {
        this.wzrost = wzrost;
        this.waga = waga;
        this.imie = imie;
        this.dzieci = new HashSet<>();
    }

    public Czlowiek() {
        this.wzrost = 0;
        this.waga = 0;
        this.imie = "";
        this.dzieci = new HashSet<>();
    }

    public void add_dzieci(Czlowiek rs) {
        dzieci.add(rs);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Czlowiek other) {
            return wzrost == other.wzrost && waga == other.waga && imie.equals(other.imie) && dzieci.equals(other.dzieci);
        }
        return false;
    }

    @Override
    public int hashCode() {
        return wzrost + waga + imie.hashCode() + dzieci.hashCode();
    }

    @Override
    public int compareTo(Czlowiek o) {
        return dzieci.size() - o.dzieci.size();
    }

    @Override
    public int compare(Czlowiek o1, Czlowiek o2) {
        return o1.wzrost - o2.wzrost;
    }

    public int potomstwo() {
        int potomstwo = dzieci.size();
        for (Czlowiek rs : dzieci) {
            potomstwo += rs.potomstwo();
        }
        return potomstwo;
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(" ").append("Czlowiek : ").append(imie)
                .append(" wzrost: ").append(wzrost)
                .append(" waga: ").append(waga)
                .append(" dzieci: ").append(potomstwo());
        if (potomstwo() > 0) {
            s.append("\n{");
            for (Czlowiek rs : dzieci) {
                s.append("\n   ").append(rs.toString());
            }
            s.append("\n}");
        }
        s.append("\n");
        return s.toString();
    }

    private double Calculation() {
        double x = 0;
        for(int i = 0; i<20000; i++){
            x += (Math.pow(2, (this.wzrost-this.waga)-i)%321443);
        }
        return x;
    }

    public double CalculationForAll() {
        double x = Calculation();
        for(Czlowiek rs : dzieci) {
            x += rs.CalculationForAll();
        }
        return x;
    }
}
