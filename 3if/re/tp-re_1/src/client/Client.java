package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import protocol.ClientRMIInterface;
import protocol.ServerRMIInterface;

public class Client implements ClientRMIInterface {
    
    private final ClientGUI myClientGUI;
    
    public boolean isConnected = false;
    public int idClient = -1;
    public ServerRMIInterface stub;
    
    public Client() {
        myClientGUI = new ClientGUI(this);
        myClientGUI.setVisible(true);
    }
    
    public void Connect(String host, String port) throws Exception {        
        Registry registry = LocateRegistry.getRegistry(host, Integer.parseInt(port));
        this.stub = (ServerRMIInterface) registry.lookup("ChatMarcArno");
        //stub.Connect(this);
    }
    
    public void Disconnect() throws Exception {
        stub.Disconnect(this.idClient);
    }

    public void SendToServer(String message) throws RemoteException {
        stub.Send(this.idClient, message);
    }
    
    @Override
    public boolean Send(String message) throws RemoteException {
       myClientGUI.AddChatText(message);
       return true;
    }

    @Override
    public boolean SendCompressed(String message) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
