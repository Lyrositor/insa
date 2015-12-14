package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import protocol.ClientRMIInterface;
import protocol.ServerRMIInterface;

public class Client implements ClientRMIInterface {
    
    public int idClient = -1;
    public ServerRMIInterface stub;
    
    public void Connect(String host, String port) throws Exception {
        System.out.println("Client.Connect(" + host + " : " + port + ")");
        
        Registry registry = LocateRegistry.getRegistry(host, Integer.parseInt(port));
        this.stub = (ServerRMIInterface) registry.lookup("ChatMarcArno");
        //stub.Connect(this);
    }
    
    public void Disconnect() throws Exception {
        stub.Disconnect(this.idClient);
    }

    @Override
    public boolean Send(String message) throws RemoteException {
        stub.Send(this.idClient, message);
        
        return true;
    }

    @Override
    public boolean SendCompressed(String message) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
