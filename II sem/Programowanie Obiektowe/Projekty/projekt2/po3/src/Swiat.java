import javax.swing.*;
import javax.swing.table.TableCellRenderer;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class Swiat extends JFrame implements ActionListener {


    Vector < Organizm > organizmy = new Vector <> ();
    Vector < Organizm > nowe = new Vector <> ();

    JTable table;
    JLabel round_count_label;
    int rounds_counter = 0;
    private int szerokosc = 6;
    private int wysokosc = 6;
    private int ruchCzlowieka;
    boolean ifRuchCzlowieka = false;


    public Swiat() {

        setTitle("Symulacja wirtualnego swiata by Filip Swiniarski 197725");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1200, 800);
        create_grid(szerokosc, wysokosc);
        menu();
        setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
        setupKeyBindings();


        inicjalizujOrganizm();
        rysowanieSwiata();

    }

    private void create_grid(int width, int height) {
        Object[][] data = new Object[width][height];
        String[] columnNames = new String[width];
        for (int i = 0; i < width; i++) {
            columnNames[i] = String.valueOf(i);
        }

        table = new JTable(data, columnNames);
        table.setRowHeight(35);
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        for (int i = 0; i < height; i++) {
            table.getColumnModel().getColumn(i).setPreferredWidth(35);
        }
        TableCellRenderer renderer = table.getDefaultRenderer(Object.class);
        ((JLabel) renderer).setHorizontalAlignment(JLabel.CENTER);
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);
        setLocationRelativeTo(null);
    }

    private void menu() {
        JPanel panel = new JPanel();
        JButton next_round_button = new JButton("Nowa runda");
        next_round_button.setSize(20, 30);
        next_round_button.addActionListener(this);

        JButton save_button = new JButton("Wczytywanie");
        save_button.setSize(20, 30);

        JButton load_button = new JButton("Zapisywanie");
        load_button.setSize(20, 30);

        round_count_label = new JLabel("Runda: 0");

        panel.add(next_round_button);
        panel.add(save_button);
        panel.add(load_button);
        panel.add(round_count_label);
        panel.setLayout(new FlowLayout(FlowLayout.CENTER));
        add(panel);
    }

    private void tura() {

        for (Organizm organizm : organizmy) {
            organizm.akcja();
        }
        gen();

    }

    private void rysowanieSwiata() {
        Collections.reverse(organizmy);
        for (Organizm organizm : organizmy) {
            organizm.rysujOrganizm();
        }
        Collections.reverse(organizmy);
    }

    private void inicjalizujOrganizm() {
        Wilk wilk = new Wilk("W", get_random_position(szerokosc), get_random_position(wysokosc), 9, 5, this);
        Wilk wilk1 = new Wilk("W", get_random_position(szerokosc), get_random_position(wysokosc), 9, 5, this);
        Antylopa antylopa = new Antylopa("A", get_random_position(szerokosc), get_random_position(wysokosc), 4, 4, this);
        Antylopa antylopa1 = new Antylopa("A", get_random_position(szerokosc), get_random_position(wysokosc), 4, 4, this);
        Zolw zolw = new Zolw("Z", get_random_position(szerokosc), get_random_position(wysokosc), 2, 1, this);
        Zolw zolw1 = new Zolw("Z", get_random_position(szerokosc), get_random_position(wysokosc), 2, 1, this);
        Lis lis = new Lis("L", get_random_position(szerokosc), get_random_position(wysokosc), 3, 7, this);
        Lis lis1 = new Lis("L", get_random_position(szerokosc), get_random_position(wysokosc), 3, 7, this);
        Owca owca = new Owca("O", get_random_position(szerokosc), get_random_position(wysokosc), 4, 4, this);
        Owca owca1 = new Owca("O", get_random_position(szerokosc), get_random_position(wysokosc), 4, 4, this);
        Trawa trawa = new Trawa("T", get_random_position(szerokosc), get_random_position(wysokosc), 0, 0, this);
        Mlecz mlecz = new Mlecz("M", get_random_position(szerokosc), get_random_position(wysokosc), 0, 0, this);
        Guarana guarana = new Guarana("G", get_random_position(szerokosc), get_random_position(wysokosc), 0, 0, this);
        WilczeJagody wilczeJagody = new WilczeJagody("WJ", get_random_position(szerokosc), get_random_position(wysokosc), 99, 0, this);
        BarszczSosnowskiego barszczSosnowskiego = new BarszczSosnowskiego("BS", get_random_position(szerokosc), get_random_position(wysokosc), 10, 0, this);
        Czlowiek czlowiek = new Czlowiek("Cz", get_random_position(szerokosc), get_random_position(wysokosc), 5, 4, this);

        organizmy.add(czlowiek);
        organizmy.add(trawa);
        organizmy.add(mlecz);
        organizmy.add(guarana);
        organizmy.add(wilczeJagody);
        organizmy.add(barszczSosnowskiego);
        organizmy.add(wilk);
        organizmy.add(wilk1);
        organizmy.add(antylopa);
        organizmy.add(antylopa1);
        organizmy.add(zolw);
        organizmy.add(zolw1);
        organizmy.add(lis);
        organizmy.add(lis1);
        organizmy.add(owca);
        organizmy.add(owca1);


    }

    public int getSzerokoscSwiata()
    {
        return szerokosc;
    }
    public int getWysokoscSwiata()
    {
        return wysokosc;
    }

    private void clear_world()
    {
        for (int i = 0; i < wysokosc; i++)
        {
            for (int j = 0; j < szerokosc; j++)
            {
                table.setValueAt(" ", i, j);
            }
        }
        nowe.clear();
    }

    public Organizm getOrganizm(int x, int y)
    {
        for (Organizm organizm : organizmy)
        {
            if ((organizm.x_pos == x) && organizm.y_pos == y)
            {
                return organizm;
            }
        }

        return null;
    }

    public int get_random_position(int rozmiar)
    {
        Random random = new Random();
        return random.nextInt(rozmiar - 1) + 1;
    }

    private void gen()
    {
        organizmy.addAll(nowe);

        Collections.sort(organizmy, new Comparator<Organizm>()
        {
            @Override
            public int compare(Organizm o1, Organizm o2) {
                return Integer.compare(o2.inicjatywa, o1.inicjatywa);
            }
        });

    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        if (ifRuchCzlowieka) {
            clear_world();
            rounds_counter++;
            round_count_label.setText("Runda: " + rounds_counter);
            tura();
            rysowanieSwiata();
            ifRuchCzlowieka = false;
        }

    }



    private void setupKeyBindings()
    {
        InputMap inputMap = getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = getRootPane().getActionMap();

        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_W, 0), "gora");
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_S, 0), "dol");
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_A, 0), "lewo");
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_D, 0), "prawo");

        actionMap.put("gora", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ruchCzlowieka = 0;
                ifRuchCzlowieka = true;
            }
        });

        actionMap.put("dol", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ruchCzlowieka = 1;
                ifRuchCzlowieka = true;
            }
        });

        actionMap.put("lewo", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ruchCzlowieka = 2;
                ifRuchCzlowieka = true;
            }
        });

        actionMap.put("prawo", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ruchCzlowieka = 3;
                ifRuchCzlowieka = true;

            }
        });
    }

    public int getRuchCzlowieka()
    {
        return ruchCzlowieka;
    }
}

