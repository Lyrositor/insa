package protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMIServerInterface extends Remote {

    String connect(String username, RMIClientInterface client)
            throws RemoteException;

    void rename(String sessionId, String newUsername) throws RemoteException;

    void send(String sessionId, String message) throws RemoteException;

    void disconnect(String sessionId) throws RemoteException;
}
