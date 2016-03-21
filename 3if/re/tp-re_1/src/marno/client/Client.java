package marno.client;

/**
 * Handles client functionality that is independent of the underlying protocol
 * implementation (RMI or sockets).
 */
abstract class Client {

    /**
     * The client's main GUI window.
     */
    protected ClientGUI window;

    /**
     * Client username (default: "User").
     */
    public String username = "User";

    /**
     * Attaches the client to a GUI window and makes it visible.
     *
     * @param window the main GUI window
     */
    public Client(ClientGUI window) {
        this.window = window;
        this.window.setVisible(true);
    }

    /**
     * Sends a connection request to the server.
     *
     * @param host address of the server
     * @param port port number of the server
     * @throws Exception if the connection fails
     */
    abstract void connect(String host, String port) throws Exception;

    /**
     * Cleanly closes the connection to the server.
     *
     * @throws Exception if the client fails to cleanly disconnect
     */
    abstract void disconnect() throws Exception;

    /**
     * Sends a public text message to the server.
     *
     * The message will be broadcast to all other clients connected to the
     * server.
     *
     * @param message the input text to sent
     * @throws Exception if an exception occurs during execution
     */
    abstract void sendMessageToServer(String message) throws Exception;

    /**
     * Sends a private message to another client connected to the server.
     *
     * @param username the username of the receiving client
     * @param message the contents of the message
     * @throws Exception if an exception occurs during execution
     */
    abstract void sendPrivateMessageToServer(String username, String message) throws Exception;

}
