package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import protocol.ClientRMIInterface;
import protocol.ServerRMIInterface;

public class ClientMain {
    
    public static void main(String[] args) {
        
        Client myClient = new Client();

        String host = (args.length < 1) ? null : args[0];
        try {
            ClientRMIInterface ref = (ClientRMIInterface) UnicastRemoteObject.exportObject(myClient, 0);
            
            Registry registry = LocateRegistry.getRegistry(host);
            ServerRMIInterface stub = (ServerRMIInterface) registry.lookup("ChatMarcArno");
            
            //String response = stub.sayHello();
        } catch (Exception e) {
            System.err.println("[Client exception]: " + e.toString());
            e.printStackTrace();
        }
    }
    
}
