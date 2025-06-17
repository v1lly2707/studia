import java.util.*;

class Resource<T> {
    private Queue<T> buff = new LinkedList<>();
    private int size;

    public Resource(int size) {
        this.size = size;
    }

    public synchronized void production(T item) throws InterruptedException {
        while (buff.size() >= size) {
            wait();
        }

        buff.add(item);
        System.out.println(Thread.currentThread().getName() + ": Produced " + item.toString());
        notifyAll();
    }

    public synchronized T consumption() throws InterruptedException {
        while (buff.isEmpty()) {
            wait();
        }

        T item = buff.poll();
        System.out.println(Thread.currentThread().getName() + ": Consumed " + item.toString());
        notifyAll();
        return item;
    }
}

class CoalMine extends Thread {
    private Resource<String> coal;
    private int d;

    public CoalMine(Resource<String> coal, int d) {
        this.coal = coal;
        this.d = d;
        setName("Coal-Mine");
    }

    public void run() {
        try {
            while (true) {
                Thread.sleep(d);
                coal.production("Coal");
            }
        } catch (InterruptedException e) {
            System.out.println("Stop");
        }
    }
}

class Princess extends Thread {
    private Resource<String> jewelry;
    private Resource<String> happiness;
    private int d;

    public Princess(Resource<String> jewelry, Resource<String> happiness, int d) {
        this.jewelry = jewelry;
        this.happiness = happiness;
        this.d = d;
        setName("Princess");
    }

    public void run() {
        try {
            while (true) {
                Thread.sleep(1000);
                jewelry.consumption();
                happiness.production("Happiness");
            }
        } catch (InterruptedException e) {
            System.out.println("Stop");
        }
    }
}

class King extends Thread {
    private Resource<String> happiness;
    private int d;

    public King(Resource<String> happiness, int d) {
        this.happiness = happiness;
        this.d = d;
        setName("King");
    }

    public void run() {
        try {
            while (true) {
                Thread.sleep(1500);
                happiness.consumption();
            }
        } catch (InterruptedException e) {
            System.out.println("Stop");
        }
    }
}

class Army extends Thread {
    private Resource<String> weapons;
    private Resource<String> tactics;
    private int d;
    private Kingdom enemy;

    public Army(Resource<String> weapons, Resource<String> tactics, Kingdom enemy, int d) {
        this.weapons = weapons;
        this.tactics = tactics;
        this.enemy = enemy;
        this.d = d;
        setName("Army: " + enemy.getName());
    }

    @Override
    public void run() {
        try {
            boolean enemyLost = false;

            while (!enemyLost) {
                Thread.sleep(d);
                enemyLost = enemy.hasLost();
                if (enemyLost) break;

                weapons.consumption();
                tactics.consumption();

                boolean success = new Random().nextBoolean();

                if (success) {
                    enemy.takeDamage();
                    System.out.println(getName() + " have beaten enemy in the battle");
                } else {
                    System.out.println(getName() + " have lost in the battle");
                }

                enemyLost = enemy.hasLost();
            }

            System.out.println(getName() + ": Wins");
            System.exit(0); // optional: ends the whole program after win
        } catch (InterruptedException e) {
            System.out.println("Stop");
        }
    }
}

class Kingdom {
    private String name;
    private int health = 15;

    public Kingdom(String name, int health) {
        this.name = name;
        this.health = health;
    }

    public String getName() {
        return name;
    }

    public synchronized void takeDamage() {
        if (health > 0) {
            health--;
            System.out.println(name + " kingdom has been given damage");
        }
    }

    public synchronized boolean hasLost() {
        return health <= 0;
    }
}

public class War {
    public static void main(String[] args) {
        Random rand = new Random();

        Kingdom a = new Kingdom("A", rand.nextInt(8) + 8);
        Kingdom b = new Kingdom("B", rand.nextInt(8) + 8);

        Resource<String> coal1 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> jewelry1 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> happiness1 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> weapons1 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> tactics1 = new Resource<>(rand.nextInt(5) + 3);

        Resource<String> coal2 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> jewelry2 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> happiness2 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> weapons2 = new Resource<>(rand.nextInt(5) + 3);
        Resource<String> tactics2 = new Resource<>(rand.nextInt(5) + 3);

        new CoalMine(coal1, rand.nextInt(500) + 500).start();
        new Princess(jewelry1, happiness1, rand.nextInt(500) + 500).start();
        new King(happiness1, rand.nextInt(500) + 500).start();
        new Army(weapons1, tactics1, b, rand.nextInt(500) + 1000).start();

        new CoalMine(coal2, rand.nextInt(500) + 500).start();
        new Princess(jewelry2, happiness2, rand.nextInt(500) + 500).start();
        new King(happiness2, rand.nextInt(500) + 500).start();
        new Army(weapons2, tactics2, a, rand.nextInt(500) + 1000).start();

        new Thread(() -> {
            try {
                while (true) {
                    Thread.sleep(rand.nextInt(400) + 600);
                    jewelry1.production("Jewelry");
                    weapons1.production("Weapon");
                    tactics1.production("Tactics");
                }
            } catch (InterruptedException e) {
            }
        }, "1").start();

        new Thread(() -> {
            try {
                while (true) {
                    Thread.sleep(rand.nextInt(400) + 600);
                    jewelry2.production("Jewelry");
                    weapons2.production("Weapon");
                    tactics2.production("Tactic");
                }
            } catch (InterruptedException e) {
            }
        }, "2").start();
    }
}
