package server;

import protocol.ClientRMIInterface;
import protocol.ServerRMIInterface;

import java.io.IOException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

class RMIServer extends Server implements ServerRMIInterface {

    public RMIServer(int serverPort, String historyFilename)
            throws IOException {
        super(serverPort, historyFilename);
    }

    public void run() throws Exception {
        ServerRMIInterface stub =
                (ServerRMIInterface) UnicastRemoteObject.exportObject(this, 0);

        // Bind the remote object's stub in the registry
        Registry registry = LocateRegistry.createRegistry(port);
        registry.bind("ChatMarcArno", stub);

        System.out.println("Server listening on port " + port);
    }

    @Override
    public String Connect(String username, ClientRMIInterface client)
            throws RemoteException {
        RMISession session = new RMISession(username, client);
        try {
            return this.addUser(session);
        } catch (Exception e) {
            throw new RemoteException("Username already in use");
        }
    }

    @Override
    public boolean Rename(String sessionId, String newUsername)
            throws RemoteException {
        try {
            this.renameUser(sessionId, newUsername);
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    @Override
    public boolean Send(String sessionId, String message)
            throws RemoteException {
        try {
            this.addMessage(sessionId, message);
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    @Override
    public boolean Disconnect(String sessionId) throws RemoteException {
        try {
            this.removeUser(sessionId);
        } catch (Exception e) {
            return false;
        }
        return true;
    }

}
