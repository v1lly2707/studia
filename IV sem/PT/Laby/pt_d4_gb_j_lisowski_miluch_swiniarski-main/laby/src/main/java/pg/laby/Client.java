package pg.laby;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.time.LocalTime;
import java.util.*;
import java.util.concurrent.*;

public class Client {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 1234);
        ObjectOutputStream stream = new ObjectOutputStream(socket.getOutputStream());

        //Generowanie ludzi PKT.1
        int watki = 4;
        CzlowiekGenerator gen = new CzlowiekGenerator(5,7);
        Vector<Czlowiek> data = new Vector<>();
        gen.generateCzlowiekVector(400,data);
        System.out.println("["+ LocalTime.now()+"]"+"Nawiązano połączenie z serwerem...");
        System.out.println("["+ LocalTime.now()+"]"+"Rozpoczęto obliczenia...");
        //Zliczanie calkowitej ilosci objektow w data
        int all = 0;
        for(Czlowiek czlowiek : data){
            all += czlowiek.potomstwo();
        }
        System.out.println("Całkowita ilość osób:" + all);

        //Stworzenie puli watkow PKT.2
        ExecutorService executor = Executors.newFixedThreadPool(watki);
        List<Callable<Double>> callableTasks = new ArrayList<>();

        long startTime = System.currentTimeMillis();
        for(Czlowiek czlowiek : data){
            callableTasks.add(czlowiek::CalculationForAll);
        }

        //Wykonywanie obliczen PKT.4
        List<Future<Double>> futures = null;
        try{
           futures = executor.invokeAll(callableTasks);
        }
        catch (InterruptedException e){
            System.out.println("Blad przy wykonywaniu watkow");
        }

        //Zbieranie wynikow PKT.3
        Vector<Double> result = new Vector<>();
        for(Future<Double> future : futures){
            try {
                result.add(future.get());
            } catch (InterruptedException | ExecutionException e) {
                throw new RuntimeException(e);
            }
        }
        executor.shutdown();
        long endTime = System.currentTimeMillis();

        System.out.println("Całkowity czas obliczeń: " + (endTime - startTime));
        System.out.println(result);
        System.out.println("["+ LocalTime.now()+"]"+"Wysyłanie rozpoczęte...");
        stream.writeObject(result);
        System.out.println("["+ LocalTime.now()+"]"+"Wysyłanie zakończone...");
        stream.close();
        socket.close();
        System.out.println("["+ LocalTime.now()+"]"+"Gnizado klienta zamknięte");
    }
}