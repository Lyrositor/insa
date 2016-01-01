package marno.client;

abstract class Client {

    /* Config */
    private final String DEFAULT_USERNAME = "Test";
    /* --- */

    protected ClientGUI window;

    public boolean isConnected = false;
    public String username = DEFAULT_USERNAME;

    public Client() {
        window = new ClientGUI(this);
        window.setVisible(true);
    }

    abstract void connect(String host, String port) throws Exception;

    abstract void disconnect() throws Exception;

    abstract void sendMessageToServer(String message) throws Exception;

    abstract void sendPrivateMessageToServer(String username, String message) throws Exception;

}
