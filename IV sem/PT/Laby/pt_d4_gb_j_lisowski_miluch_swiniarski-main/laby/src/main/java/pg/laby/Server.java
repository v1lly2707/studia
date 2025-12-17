package pg.laby;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    //LOGI
    public static void main(String[] args) {
        try(ServerSocket serverSocket = new ServerSocket(1234)){
            System.out.println("Serwer wystartował w sieci lokalnej. Oczekiwanie na klientów...");

            while(true) {
                Socket clientSocket = serverSocket.accept();
                var connectionHandler = new Thread(new ConnectionHandler(clientSocket));
                connectionHandler.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
