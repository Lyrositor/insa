package protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.LinkedList;

public interface RMIClientInterface extends Remote {

    void ping() throws RemoteException;

    void sendMessage(String date, String message) throws RemoteException;

    void sendHistory(LinkedList<String> history) throws RemoteException;

    void sendPrivateMessage(String date, String username, String message)
            throws RemoteException;

    void sendUserList(String[] users) throws RemoteException;
}
