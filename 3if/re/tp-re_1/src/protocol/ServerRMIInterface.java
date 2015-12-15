package protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ServerRMIInterface extends Remote {

    String Connect(String username, ClientRMIInterface client)
            throws RemoteException;

    boolean Rename(String sessionId, String newUsername) throws RemoteException;

    boolean Send(String sessionId, String message) throws RemoteException;

    boolean Disconnect(String sessionId) throws RemoteException;
}
