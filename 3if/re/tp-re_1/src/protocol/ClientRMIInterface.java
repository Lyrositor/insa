package protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ClientRMIInterface extends Remote {

    boolean Send(String message) throws RemoteException;

    void Ping() throws RemoteException;
}
