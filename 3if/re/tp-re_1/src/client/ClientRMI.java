package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import javax.swing.DefaultListModel;
import protocol.ClientRMIInterface;
import protocol.Config;
import protocol.ServerRMIInterface;

public class ClientRMI extends Client implements ClientRMIInterface {
    
    private String sessionId;
    private ServerRMIInterface stub;
    
    @Override
    public void Connect(String host, String port) throws Exception {
        Registry registry = LocateRegistry.getRegistry(host, Integer.parseInt(port));
        stub = (ServerRMIInterface) registry.lookup(Config.REGISTRY_NAME);
        window.textAreaChat.setText("");
        
        try {
            sessionId = stub.Connect(username, this);
        } catch (RemoteException e) {
            // Handle invalid username
        }
    }
    
    @Override
    public void Disconnect() throws Exception {
        stub.Disconnect(this.sessionId);
    }
    
    @Override
    public void SendToServer(String message) throws RemoteException {
        stub.Send(this.sessionId, message);
    }
    
    @Override
    public void Send(String message) throws RemoteException {
       window.addChatText(message);
    }

    @Override
    public void SendListUser(String[] users) throws RemoteException {
        DefaultListModel listModel = new DefaultListModel();
        for(String user : users) {
            listModel.addElement(user);
        }
        window.listUser.setModel(listModel);
    }

    @Override
    public void Ping() throws RemoteException {
    }
    
}
