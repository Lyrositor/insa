package client;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

public class ClientSocket extends Client implements Runnable {

    Socket socketServer = null;
    PrintStream socketOut = null;
    BufferedReader socketIn = null;

    @Override
    void Connect(String host, String port) throws Exception {
        socketServer = new Socket(host, Integer.parseInt(port));

        socketIn = new BufferedReader(new InputStreamReader(socketServer.getInputStream()));
        socketOut = new PrintStream(socketServer.getOutputStream());

        socketOut.println("CONNECT " + username + "\n");

        this.run();
    }

    @Override
    void Disconnect() throws Exception {
        socketOut.println("QUIT\n");
        socketOut.close();
        socketIn.close();
        socketServer.close();
    }

    @Override
    void SendToServer(String message) throws Exception {
        socketOut.println("SENDTO all CONTENT " + message + "\n");
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
        String[] elements = line.split(" ");
        switch (elements[0]) {
            case "SIGNIN":
                window.addChatText("server > all : " + elements[1] + "signed in...\n");
                break;

            case "SIGNOUT":
                window.addChatText("server > all : " + elements[1] + "signed out...\n");
                break;

            case "MESSAGE":
                window.addChatText(elements[2] + " > " + elements[4] + " : " + elements[6] + "\n");
                break;

            default:
                System.err.println("Unrecognized: " + line);
                break;
        }
    }

}
