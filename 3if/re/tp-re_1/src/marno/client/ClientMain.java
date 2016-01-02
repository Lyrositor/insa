package marno.client;

/**
 * Main class for client
 */
public class ClientMain {

    /**
     * Main function, firstly executed, who defined the graphical style and launch the window
     * 
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

        ClientGUI clientGui = new ClientGUI();
        clientGui.setVisible(true);
    }

}
