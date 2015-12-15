package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import protocol.ClientRMIInterface;
import protocol.Config;
import protocol.ServerRMIInterface;

public class ClientRMI extends Client implements ClientRMIInterface {
    
    @Override
    public void Connect(String host, String port) throws Exception {
        Registry registry = LocateRegistry.getRegistry(host, Integer.parseInt(port));
        stub = (ServerRMIInterface) registry.lookup(Config.REGISTRY_NAME);
        window.textAreaChat.setText("");
        
        try {
            sessionId = stub.Connect(username, this);
        } catch (RemoteException e) {
            // Handle invalid username
        }
    }
    
    @Override
    public void Disconnect() throws Exception {
        stub.Disconnect(this.sessionId);
    }
    
    @Override
    public void SendToServer(String message) throws RemoteException {
        stub.Send(this.sessionId, message);
    }
    
}
