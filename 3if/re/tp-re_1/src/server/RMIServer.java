package server;

import java.io.IOException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import protocol.RMIConfig;
import protocol.RMIClientInterface;
import protocol.MarnoProtocol;
import protocol.RMIServerInterface;
import server.exceptions.ServerException;

class RMIServer extends Server implements RMIServerInterface {

    public RMIServer(int serverPort, String historyFilename)
            throws IOException {
        super(serverPort, historyFilename);
    }

    public void run() throws Exception {
        RMIServerInterface stub =
                (RMIServerInterface) UnicastRemoteObject.exportObject(this, 0);

        // Bind the remote object's stub in the registry
        Registry registry = LocateRegistry.createRegistry(port);
        registry.bind(RMIConfig.REGISTRY_NAME, stub);

        System.out.println("Server listening on port " + port);
    }

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

    @Override
    public void send(String sessionId, String message)
            throws RemoteException {
        try {
            addMessage(sessionId, message);
        } catch (ServerException e) {
            throw new RemoteException(
                    MarnoProtocol.ERROR_MESSAGES[e.getCode()], e);
        }
    }

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
