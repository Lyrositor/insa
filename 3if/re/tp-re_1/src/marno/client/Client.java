package marno.client;

/**
 * Common class for types of client, with common methods
 */
abstract class Client {

    /**
     * Link to the main GUI window who hosting the client
     */
    protected ClientGUI window;

    /**
     * Client username with a default value
     */
    public String username = "User";

    /**
     * Client constructor, call in daughter by super()
     * @param window the main GUI window
     */
    public Client(ClientGUI window) {
        this.window = window;
        this.window.setVisible(true);
    }

    /**
     * Method for connect to the server. Need to be reimplanted
     * @param host address of the server
     * @param port number of the server
     * @throws Exception if connection fail
     */
    abstract void connect(String host, String port) throws Exception;

    /**
     * Close the connection to the server properly. Need to be reimplanted
     * @throws Exception if a problem appear
     */
    abstract void disconnect() throws Exception;

    /**
     * Send a classical message (text) of the chat to the server for all people. Need to be reimplanted
     * @param message the input text to sent
     * @throws Exception 
     */
    abstract void sendMessageToServer(String message) throws Exception;

    /**
     * Send a private message to a specific person. Need to be reimplanted
     * @param username the name of the person who received the message
     * @param message the input text to sent
     * @throws Exception 
     */
    abstract void sendPrivateMessageToServer(String username, String message) throws Exception;

}
