package client;

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

    abstract void Connect(String host, String port) throws Exception;

    abstract void Disconnect() throws Exception;

    abstract void SendToServer(String message) throws Exception;
    
}
