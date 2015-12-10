package server;

import java.rmi.RemoteException;
import protocol.ClientRMIInterface;
import protocol.ServerRMIInterface;

public class Server implements ServerRMIInterface {

    @Override
    public boolean Connect(ClientRMIInterface client) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean Send(int clientId, String message) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean Disconnect(int clientId) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
