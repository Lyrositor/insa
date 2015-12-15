package client;

import java.rmi.RemoteException;
import protocol.ClientRMIInterface;
import protocol.ServerRMIInterface;

abstract class Client implements ClientRMIInterface {

    /* Config */
    private final String DEFAULT_USERNAME = "UsernameTest";
    /* --- */
    
    protected ClientGUI window;
    
    public boolean isConnected = false;
    public String username = DEFAULT_USERNAME;
    public String sessionId;
    public ServerRMIInterface stub;

    public Client() {
        window = new ClientGUI(this);
        window.setVisible(true);
    }

    abstract void Connect(String host, String port) throws Exception;

    abstract void Disconnect() throws Exception;

    abstract void SendToServer(String message) throws Exception;

    @Override
    public void Ping() {
    }

    @Override
    public boolean Send(String message) throws RemoteException {
       window.addChatText(message);
       return true;
    }

}
