package client;

import java.rmi.server.UnicastRemoteObject;
import protocol.ClientRMIInterface;

public class ClientMain {
    
    public static void main(String[] args) {
        
        /* Nimbus style */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(ClientGUIConnect.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        
        Client myClient = new Client();
        
        ClientGUI myClientGUI = new ClientGUI(myClient);
        myClientGUI.setVisible(true);

        try {
            ClientRMIInterface ref = (ClientRMIInterface) UnicastRemoteObject.exportObject(myClient, 0);

            //String response = stub.sayHello();
        } catch (Exception e) {
            System.err.println("[Client exception]: " + e.toString());
            e.printStackTrace();
        }
    }
    
}
