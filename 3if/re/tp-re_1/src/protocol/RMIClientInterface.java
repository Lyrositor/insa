package protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMIClientInterface extends Remote {

    void ping() throws RemoteException;

    void send(String message) throws RemoteException;

    void sendUserList(String[] users) throws RemoteException;
}
