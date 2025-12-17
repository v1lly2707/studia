package pg.laby;

import java.io.*;
import java.util.UUID;
import java.util.Vector;

public class CzlowiekGenerator {
    public int maxGlebokosc;
    public int maxDzieci;

    public CzlowiekGenerator(int maxGlebokosc, int maxDzieci) {
        this.maxGlebokosc = maxGlebokosc;
        this.maxDzieci = maxDzieci;
    }

    public Czlowiek generateCzlowiek(){
        return generateCzlowiek(maxGlebokosc);
    }

    public void generateCzlowiekVector(int n, Vector<Czlowiek> set) {
        for(int i = 0; i < n; i++){
            set.add(generateCzlowiek());
        }
    }

    private Czlowiek generateCzlowiek(int glebokosc) {
        Czlowiek czlowiek = new Czlowiek((int) (Math.random() * 200), (int) (Math.random() * 100), UUID.randomUUID().toString());
        if (glebokosc > 0) {
            int dzieci = (int) (Math.random() * maxDzieci);
            for (int i = 0; i < dzieci; i++) {
                czlowiek.add_dzieci(generateCzlowiek(glebokosc - 1));
            }
        }
        return czlowiek;
    }

    public static Vector<Czlowiek> getFromFile(String filename, int n, int maxGlebokosc, int maxDzieci) {
        File file = new File(filename);
        Vector<Czlowiek> data = new Vector<>();

        if (file.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
                data = (Vector<Czlowiek>) ois.readObject();
                System.out.println("Zaladowano dane z: " + filename);
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        } else {
            CzlowiekGenerator generator = new CzlowiekGenerator(maxGlebokosc, maxDzieci);
            generator.generateCzlowiekVector(n, data);
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file))) {
                oos.writeObject(data);
                System.out.println("Dane wygenerowane i zapisane do: " + filename);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return data;
    }
}
