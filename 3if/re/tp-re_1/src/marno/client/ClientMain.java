package marno.client;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.UIManager;

/**
 * Main client class; creates and runs a new GUI client window.
 */
public class ClientMain {

    /**
     * Defines the preferred look and feel, then creates a new window.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        /* Nimbus style */
        try {
            for (UIManager.LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | javax.swing.UnsupportedLookAndFeelException ex) {
            Logger.getLogger(ClientGUIConnect.class.getName()).log(Level.SEVERE, null, ex);
        }

        ClientGUI clientGui = new ClientGUI();
        clientGui.setVisible(true);
    }

}
