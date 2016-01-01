package marno.client;

import marno.protocol.MarnoProtocol;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.LinkedList;
import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;
import static marno.protocol.MarnoProtocol.ERROR_MESSAGES;

public class SocketClient extends Client implements Runnable {

    private Socket socketServer = null;
    private PrintStream socketOut = null;
    private BufferedReader socketIn = null;

    private volatile boolean listening = true;
    private Thread mainThread = null;
    private Thread pingThread = null;

    @Override
    void connect(String host, String port) throws Exception {
        socketServer = new Socket(host, Integer.parseInt(port));
        socketServer.setSoTimeout(MarnoProtocol.TIMEOUT);

        socketIn = new BufferedReader(new InputStreamReader(socketServer.getInputStream()));
        socketOut = new PrintStream(socketServer.getOutputStream());

        socketOut.println("CONNECT " + username);

        mainThread = new Thread(this);
        mainThread.start();
        pingThread = new Thread(new Runnable() {
            public void run() {
                while (listening) {
                    socketOut.println("PING");
                    try {
                        synchronized (this) {
                            wait(MarnoProtocol.PING_FREQUENCY);
                        }
                    } catch (InterruptedException e) {
                        return;
                    }
                }
            }
        });
        pingThread.start();
    }

    @Override
    void disconnect() throws Exception {
        synchronized (pingThread) {
            pingThread.notify();
        }
        socketOut.println("DISCONNECT");

        listening = false;

        socketOut.close();
        socketIn.close();
        socketServer.close();
    }

    @Override
    void sendMessageToServer(String message) throws Exception {
        socketOut.println("MSG " + message);
    }

    @Override
    void sendPrivateMessageToServer(String username, String message) throws Exception {
        socketOut.println("PRIVATE " + username + " " + message);
    }

    @Override
    public void run() {
        String line;
        listening = true;
        try {
            while (listening && (line = socketIn.readLine()) != null) {
                handleInput(line);
            }
        } catch (IOException e) {
            System.out.println("INFO: Closing socket with server");
        }
    }

    private void handleInput(String input) {
        String[] elements = input.split(" ", 2);
        String[] subElements;
        System.out.println("SERVER: " + input);

        switch (elements[0]) {
            case "PONG":
                break;

            case "HISTORY":
                // Handle history
                // Format : HISTORY <num> <len1> <msg1> <len2> <msg2> ...
                subElements = elements[1].split(" ", 2);
                int numMessages = Integer.parseInt(subElements[0]);
                int idx = 0;
                LinkedList<String> history = new LinkedList<>();
                for (int i = 0; i < numMessages; i++) {
                    int w = subElements[1].indexOf(' ', idx);
                    int len = Integer.parseInt(subElements[1].substring(idx, w));
                    history.add(subElements[1].substring(w + 1, w + len + 1));
                    idx = w + len + 2;
                }
                window.addChatText(String.join("\n", history), false);
                break;

            case "MSG":
                // Handle normal message
                window.addChatText(elements[1]);
                break;

            case "PRIVATE":
                // Handle private message
                subElements = elements[1].split(" ", 3);
                window.addChatText(
                        subElements[0] + " {" + subElements[1] + "} " +
                        subElements[2]
                );
                break;

            case "USERS":
                // Handle user list
                String[] users = elements[1].split(" ");
                DefaultListModel<String> listModel = new DefaultListModel<>();
                for (String user : users) {
                    listModel.addElement(user);
                }
                window.listUser.setModel(listModel);
                break;

            case "ERROR":
                // Handle error
                int errorNumber = Integer.parseInt(elements[1]);
                JOptionPane.showMessageDialog(
                        null, ERROR_MESSAGES[errorNumber], "Error",
                        JOptionPane.ERROR_MESSAGE
                );

                if (errorNumber == 1) { // Invalid username => disconnect
                    window.disconnect();
                }
                break;

            default:
                System.err.println("Unrecognized: " + input);
                break;
        }
    }

}
