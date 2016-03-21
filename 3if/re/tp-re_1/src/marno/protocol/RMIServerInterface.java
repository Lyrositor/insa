package marno.protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * The RMI interface implemented by RMI servers.
 */
public interface RMIServerInterface extends Remote {

    /**
     * Sends a connection request to the RMI server.
     *
     * @param username the initial username value for the client
     * @param client the RMI client trying to connect
     * @return the session ID
     * @throws RemoteException if an error occurred
     */
    String connect(String username, RMIClientInterface client)
            throws RemoteException;

    /**
     * Changes the client's username.
     *
     * @param sessionId the client's session ID
     * @param newUsername the new value of the client's username
     * @throws RemoteException if an error occurred
     */
    void rename(String sessionId, String newUsername) throws RemoteException;

    /**
     * Sends a new public message to the server from this client.
     *
     * @param sessionId the client's session ID
     * @param message the message contents
     * @throws RemoteException if an error occurred
     */
    void sendMessage(String sessionId, String message) throws RemoteException;

    /**
     * Sends a new private message to another client.
     *
     * @param sessionId the client's session ID
     * @param username the username of the destination user
     * @param message the message contents
     * @throws RemoteException if an error occurred
     */
    void sendPrivateMessage(String sessionId, String username, String message)
            throws RemoteException;

    /**
     * Disconnects this client from the server.
     *
     * @param sessionId the client's session ID
     * @throws RemoteException if an error occurred
     */
    void disconnect(String sessionId) throws RemoteException;
}
