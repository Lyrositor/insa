package protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ClientRMIInterface extends Remote {

    void Send(String message) throws RemoteException;

    void Ping() throws RemoteException;
    
    void SendListUser(String[] users) throws RemoteException;
}
