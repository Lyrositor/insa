package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import protocol.ClientRMIInterface;
import protocol.Config;
import protocol.ServerRMIInterface;

public class Client implements ClientRMIInterface {

    private final ClientGUI window;

    public boolean isConnected = false;
    public String username = Config.DEFAULT_USERNAME;
    public String sessionId;
    public ServerRMIInterface stub;

    public Client() {
        window = new ClientGUI(this);
        window.setVisible(true);
    }

    public void Connect(String host, String port) throws Exception {
        Registry registry = LocateRegistry.getRegistry(host, Integer.parseInt(port));
        stub = (ServerRMIInterface) registry.lookup(Config.REGISTRY_NAME);
        try {
            window.textAreaChat.setText("");
            sessionId = stub.Connect(username, this);
        } catch (RemoteException e) {
            // Handle invalid username
        }
    }

    public void Disconnect() throws Exception {
        stub.Disconnect(this.sessionId);
    }

    public void SendToServer(String message) throws RemoteException {
        stub.Send(this.sessionId, message);
    }

    @Override
    public boolean Send(String message) throws RemoteException {
       window.addChatText(message);
       return true;
    }

}
