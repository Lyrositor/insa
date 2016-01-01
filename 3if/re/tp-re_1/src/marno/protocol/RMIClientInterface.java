package marno.protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.LinkedList;

/**
 * The RMI interface implemented by RMI clients.
 */
public interface RMIClientInterface extends Remote {

    /**
     * Pings the client.
     *
     * @throws RemoteException if an error occurred
     */
    void ping() throws RemoteException;

    /**
     * Sends a history of old messages the server had received.
     *
     * @param history the list of messages
     * @throws RemoteException if an error occurred
     */
    void sendHistory(LinkedList<String> history) throws RemoteException;

    /**
     * Relays a public message to the client.
     *
     * @param date the date on which the message was received
     * @param message the contents of the message
     * @throws RemoteException if an error occurred
     */
    void sendMessage(String date, String message) throws RemoteException;

    /**
     * Relays a private message to the client from another user.
     *
     * @param date the date on which the message was received
     * @param username the username of the sender of the message
     * @param message the contents of the message
     * @throws RemoteException if an error occurred
     */
    void sendPrivateMessage(String date, String username, String message)
            throws RemoteException;

    /**
     * Sends a list of users currently connected to the RMI server.
     *
     * @param users a list of users currently connected to the server
     * @throws RemoteException if an error occurred
     */
    void sendUserList(String[] users) throws RemoteException;
}
