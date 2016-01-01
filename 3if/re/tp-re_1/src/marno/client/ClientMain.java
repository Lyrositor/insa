package marno.client;

import java.rmi.server.UnicastRemoteObject;
import javax.swing.JOptionPane;
import marno.protocol.RMIClientInterface;

public class ClientMain {

    /**
     * @param args the command line arguments
     */
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

        int dialogResult = JOptionPane.showConfirmDialog(null, "RMI connection?\n(Yes = RMI  |  No = Socket)", "Question", 0);
        if(dialogResult == JOptionPane.YES_OPTION) {
            // RMI
            RMIClient clientRMI = new RMIClient();

            try {
                RMIClientInterface ref = (RMIClientInterface) UnicastRemoteObject.exportObject(clientRMI, 0);
            } catch (Exception e) {
                System.err.println("[Client exception]: " + e.getMessage());
            }
        } else {
            // Socket
            SocketClient socketClient = new SocketClient();
        }
    }

}
