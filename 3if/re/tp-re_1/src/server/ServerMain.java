package server;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import protocol.ServerRMIInterface;

public class ServerMain {
    
    final static private int PORT = 1099;
    
    public static void main(String args[]) {

        try {
            Server myServ = new Server();
            ServerRMIInterface stub = (ServerRMIInterface) UnicastRemoteObject.exportObject(myServ, 0);

            // Bind the remote object's stub in the registry
            Registry registry = LocateRegistry.createRegistry(PORT);
            registry.bind("ChatMarcArno", stub);

            System.err.println("Server listen to port " + PORT);
			
        } catch (Exception e) {
            System.err.println("[Server exception]: " + e.toString());
            e.printStackTrace();
        }
    }
    
}
