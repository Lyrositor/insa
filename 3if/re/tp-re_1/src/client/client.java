package client;

import java.rmi.RemoteException;
import protocol.ClientRMIInterface;

public class Client implements ClientRMIInterface {

    @Override
    public boolean Send(String message) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean SendCompressed(String message) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
