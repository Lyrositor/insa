package marno.server;

import java.io.IOException;
import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import marno.protocol.RMIConfig;
import marno.protocol.RMIClientInterface;
import marno.protocol.MarnoProtocol;
import marno.protocol.RMIServerInterface;
import marno.server.exceptions.ServerException;

/**
 * The RMI implementation of the Marno server.
 */
class RMIServer extends Server implements RMIServerInterface {

    /**
     * Constructs a new server, ready to be run.
     *
     * @param serverPort the port to listen on
     * @param historyFilename the filename of the history file
     * @throws IOException if the history file could not be opened
     */
    public RMIServer(int serverPort, String historyFilename)
            throws IOException {
        super(serverPort, historyFilename);
    }

    /**
     * Initializes the RMI registry and binds the server to it.
     *
     * @throws AlreadyBoundException if an entity with the same name was already
     * bound
     * @throws RemoteException if the server could not be exported
     */
    @Override
    public void run() throws AlreadyBoundException, RemoteException {
        RMIServerInterface stub =
                (RMIServerInterface) UnicastRemoteObject.exportObject(this, 0);

        // Bind the remote object's stub in the registry
        Registry registry = LocateRegistry.createRegistry(port);
        registry.bind(RMIConfig.REGISTRY_NAME, stub);

        System.out.println("RMI Server listening on port " + port);
    }

    /**
     * Accepts a connection from a client.
     *
     * @param username the client's username
     * @param client the RMI client requesting the connection
     * @return the new user's session ID
     * @throws RemoteException if a new user could not be added
     */
    @Override
    public String connect(String username, RMIClientInterface client)
            throws RemoteException {
        RMISession session = new RMISession(username, client);
        try {
            return addUser(session);
        } catch (ServerException e) {
            throw new RemoteException(
                    MarnoProtocol.ERROR_MESSAGES[e.getCode()], e);
        }
    }

    /**
     * Changes a user's username to a new, valid value.
     *
     * @param sessionId the client's session ID
     * @param newUsername the new username for the client
     * @throws RemoteException if the session ID is invalid or if the user could
     * not be renamed
     */
    @Override
    public void rename(String sessionId, String newUsername)
            throws RemoteException {
        try {
            renameUser(sessionId, newUsername);
        } catch (ServerException e) {
            throw new RemoteException(
                    MarnoProtocol.ERROR_MESSAGES[e.getCode()], e);
        }
    }

    /**
     * Accepts a message from a client and broadcasts it to other clients.
     *
     * @param sessionId the emitting client's session ID
     * @param message the emitting client's message
     * @throws RemoteException if the session ID is invalid
     */
    @Override
    public void sendMessage(String sessionId, String message)
            throws RemoteException {
        try {
            addMessage(sessionId, message);
        } catch (ServerException e) {
            throw new RemoteException(
                    MarnoProtocol.ERROR_MESSAGES[e.getCode()], e);
        }
    }

    /**
     * Accepts a private message from a client and relays it.
     *
     * @param sessionId the emitting client's session ID
     * @param username the destination client's username
     * @param message the emitting client's message
     * @throws RemoteException if the session ID is invalid or if the
     * destination could not be found
     */
    @Override
    public void sendPrivateMessage(
            String sessionId, String username, String message
    ) throws RemoteException {
        try {
            addPrivateMessage(sessionId, username, message);
        } catch (ServerException e) {
            throw new RemoteException(
                    MarnoProtocol.ERROR_MESSAGES[e.getCode()], e);
        }
    }

    /**
     * Disconnects a client from the server.
     *
     * @param sessionId the disconnecting client's session ID
     * @throws RemoteException if the session ID is invalid
     */
    @Override
    public void disconnect(String sessionId) throws RemoteException {
        try {
            removeUser(sessionId);
        } catch (ServerException e) {
            throw new RemoteException(
                    MarnoProtocol.ERROR_MESSAGES[e.getCode()], e);
        }
    }

}
