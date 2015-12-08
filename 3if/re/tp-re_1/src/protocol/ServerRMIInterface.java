package protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ServerRMIInterface extends Remote {
    
    boolean Connect(ClientRMIInterface client) throws RemoteException;
    
    boolean Send(int clientId, String message) throws RemoteException;    
    
    boolean Disconnect(int clientId) throws RemoteException;
}
