package pg.laby;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.time.LocalTime;
import java.util.Vector;

public class ConnectionHandler implements Runnable {
    private final Socket clientSocket;
    private final ObjectInputStream inputStream;

    public ConnectionHandler(Socket clientSocket) throws IOException {
        this.clientSocket = clientSocket;
        inputStream = new ObjectInputStream(clientSocket.getInputStream());
    }

    @Override
    public void run() {
        System.out.println("["+ LocalTime.now()+"]"+"Nowy klient połaczony...");
        try{
            System.out.println("["+ LocalTime.now()+"]"+"Oczekiwanie na dane z klienta...");
            Vector<Double> message = (Vector<Double>) inputStream.readObject();
            System.out.println("["+ LocalTime.now()+"]"+"Odbieranie zakończone...");
            System.out.println(message);
        }
        catch (ClassNotFoundException | IOException e){
            e.printStackTrace();
        }
        close();

    }


    private void close() {
        try {
            inputStream.close();
            System.out.println("["+ LocalTime.now()+"]"+"Gniazdo klienta zamknięte");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
