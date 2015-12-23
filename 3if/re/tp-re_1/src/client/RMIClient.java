package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import javax.swing.DefaultListModel;
import protocol.RMIClientInterface;
import protocol.RMIConfig;
import protocol.RMIServerInterface;

public class RMIClient extends Client implements RMIClientInterface {

    private String sessionId;
    private RMIServerInterface stub;

    @Override
    public void Connect(String host, String port) throws Exception {
        Registry registry = LocateRegistry.getRegistry(host, Integer.parseInt(port));
        stub = (RMIServerInterface) registry.lookup(RMIConfig.REGISTRY_NAME);
        window.textAreaChat.setText("");

        try {
            sessionId = stub.connect(username, this);
        } catch (RemoteException e) {
            // Handle invalid username
        }
    }

    @Override
    public void Disconnect() throws Exception {
        stub.disconnect(this.sessionId);
    }

    @Override
    public void SendToServer(String message) throws RemoteException {
        stub.send(this.sessionId, message);
    }

    @Override
    public void send(String message) throws RemoteException {
       window.addChatText(message);
    }

    @Override
    public void sendUserList(String[] users) throws RemoteException {
        DefaultListModel listModel = new DefaultListModel();
        for(String user : users) {
            listModel.addElement(user);
        }
        window.listUser.setModel(listModel);
    }

    @Override
    public void ping() throws RemoteException {
    }

}
