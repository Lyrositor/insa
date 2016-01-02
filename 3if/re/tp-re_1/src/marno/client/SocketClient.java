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

/**
 * Implementation of the Client class for Socket connection
 */
public class SocketClient extends Client implements Runnable {

    /**
     * The socket linked to the server
     */
    private Socket socketServer = null;
    /**
     * The out stream for send informations to the server
     */
    private PrintStream socketOut = null;
    /**
     * The input stream for receive informations from the server
     */
    private BufferedReader socketIn = null;

    /**
     * Know if the client if listening to the server or not
     */
    private volatile boolean listening = true;
    /**
     * Main thread of the client to receive informations
     */
    private Thread mainThread = null;
    /**
     * Ping-pong thread with the server to know if the connection if lost
     */
    private Thread pingThread = null;

    /**
     * Constructor with the main GUI window
     * @param window the main GUI window
     */
    public SocketClient(ClientGUI window) {
        super(window);
    }

    /**
     * Launch a connection with the server, at the host with the port number.
     * Launch two threads too, one to receive informations, and another to ping-pong
     * @param host the hostname of the server
     * @param port the port number of the server
     * @throws Exception raise an exception if connection fail
     */
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

    /**
     * Close the connection with the server properly
     * @throws Exception raise an exception if a problem appear
     */
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

    /**
     * Send a message to all people of the server with the output stream
     * @param message the message to sent
     * @throws Exception raise an exception if a problem appear
     */
    @Override
    void sendMessageToServer(String message) throws Exception {
        socketOut.println("MSG " + message);
    }

    /**
     * Send a private message to an user at the server with the output stream
     * @param username the user who receive the message
     * @param message the message to sent
     * @throws Exception raise an exception if a problem appear
     */
    @Override
    void sendPrivateMessageToServer(String username, String message) throws Exception {
        socketOut.println("PRIVATE " + username + " " + message);
    }

    /**
     * The running thread who receive informations, and handle it in the handleInput function
     */
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

    /**
     * Handle the information from the server, and update the graphical elements
     * @param input the information
     */
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
                        subElements[0] + " {" + subElements[1] + "} "
                        + subElements[2]
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
