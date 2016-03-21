package marno.client;

import marno.protocol.MarnoProtocol;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.LinkedList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;
import static marno.protocol.MarnoProtocol.ERROR_MESSAGES;

/**
 * The socket implementation of the Marno client.
 */
public class SocketClient extends Client implements Runnable {

    /**
     * The server-side socket, read for incoming commands.
     *
     * Warning: The socket should not be read from directly. Use
     * {@code socketIn} instead.
     */
    private Socket socketServer = null;

    /**
     * The output stream used to send commands to the server.
     */
    private PrintStream socketOut = null;

    /**
     * The input stream used to receive commands from the server.
     */
    private BufferedReader socketIn = null;

    /**
     * Whether the client is currently listening for input from the server.
     */
    private volatile boolean listening = true;

    /**
     * Main client thread.
     *
     * Listens for input from the server.
     */
    private Thread mainThread = null;

    /**
     * Secondary thread which constantly pings the server, to keep the
     * connection active.
     */
    private Thread pingThread = null;

    /**
     * Ties the client to its GUI window.
     * @param window the client's main GUI window
     */
    public SocketClient(ClientGUI window) {
        super(window);
    }

    /**
     * Initiates a connection with the specified server, then starts two
     * threads: one to receive input from the server, another to continuously
     * ping it.
     *
     * @param host the hostname of the server
     * @param port the port number of the server
     * @throws Exception if an error occurs
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
     * Closes the connection with the server.
     *
     * @throws Exception if the client is unable to disconnect cleanly
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
     * Sends a public message to the server.
     *
     * @param message the contents of the message
     * @throws Exception raise an exception if a problem appear
     */
    @Override
    void sendMessageToServer(String message) throws Exception {
        socketOut.println("MSG " + message);
    }

    /**
     * Sends a private message to another client connected to the server.
     *
     * @param username the username of the intended recipient
     * @param message the contents of the message
     * @throws Exception if an error occurs
     */
    @Override
    void sendPrivateMessageToServer(String username, String message) throws Exception {
        socketOut.println("PRIVATE " + username + " " + message);
    }

    /**
     * Listens for incoming messages from the server.
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
     * Handle the commands from the server, and update the graphical elements.
     *
     * @param input an incoming command
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

                if (errorNumber == 1) {
                    // Invalid username => disconnect
                    try {
                        this.disconnect();
                        window.disconnect();
                    } catch (Exception e) {
                         System.err.println("[Client exception]: " + e.getMessage());
                    }
                }
                break;

            default:
                System.err.println("Unrecognized: " + input);
                break;
        }
    }

}
