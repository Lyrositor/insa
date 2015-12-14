package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import protocol.ClientRMIInterface;
import protocol.ServerRMIInterface;

public class Client implements ClientRMIInterface {
    
    public String host;
    public String port;
    
    public void Connect(String host, String port) throws Exception {
        this.host = host;
        this.port = port;
        
        System.out.println("Client.Connect(" + this.host + " : " + this.port + ")");
        
        Registry registry = LocateRegistry.getRegistry(this.host, Integer.parseInt(port));
        ServerRMIInterface stub = (ServerRMIInterface) registry.lookup("ChatMarcArno");
    }

    @Override
    public boolean Send(String message) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean SendCompressed(String message) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
