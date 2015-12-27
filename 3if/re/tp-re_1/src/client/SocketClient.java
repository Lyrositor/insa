package client;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

public class SocketClient extends Client implements Runnable {

    private Socket socketServer = null;
    private PrintStream socketOut = null;
    private BufferedReader socketIn = null;
    private Thread thread = null;

    @Override
    void Connect(String host, String port) throws Exception {
        socketServer = new Socket(host, Integer.parseInt(port));

        socketIn = new BufferedReader(new InputStreamReader(socketServer.getInputStream()));
        socketOut = new PrintStream(socketServer.getOutputStream());

        socketOut.println("CONNECT " + username);

        thread = new Thread(this);
        thread.start();
    }

    @Override
    void Disconnect() throws Exception {
        socketOut.println("DISCONNECT\n");
        socketOut.close();
        socketIn.close();
        socketServer.close();
    }

    @Override
    void SendToServer(String message) throws Exception {
        socketOut.println("MSG " + message + "\n");
    }

    @Override
    public void run() {
        String line;
        try {
            // !Thread.currentThread().isInterrupted() &&
            while ((line = socketIn.readLine()) != null) {
                handleMessage(line);
            }
        } catch (Exception e) {
            System.err.println("[Client exception]: " + e.getMessage());
        }
    }

    private void handleMessage(String line) {
        String[] elements = line.split(" ", 2);
        switch (elements[0]) {
            case "HISTORY":
                // Handle history
                // Format : HISTORY <num> <len1> <msg1> <len2> <msg2> ...
                break;

            case "MSG":
                window.addChatText(elements[1]);
                break;

            case "PRIVATE":
                // Handle private message
                break;

            case "USERS":
                // Handle user list
                break;

            default:
                System.err.println("Unrecognized: " + line);
                break;
        }
    }

}
