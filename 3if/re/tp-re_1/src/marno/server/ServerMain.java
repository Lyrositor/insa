package marno.server;

/**
 * Main server class; lets the user choose between starting an RMI server or a
 * socket server.
 */
public class ServerMain {

    /**
     * The filename of the message history log to read from and write to.
     */
    final static private String HISTORY_FILENAME = "MarnoChat.log";

    /**
     * The default port to listen on.
     */
    final static private int PORT = 1099;

    /**
     * Starts a new server instance, either as an RMI or socket server.
     *
     * If 'rmi' is passed as a command-line argument, the server will start in
     * RMI mode; otherwise, it will start in socket mode.
     * @param args optional command-line arguments
     */
    public static void main(String args[]) {
        Server chatServer;
        boolean useRMI = false;

        if (args.length > 0)
            useRMI = args[0].equals("rmi");

        try {
            if (useRMI)
                chatServer = new RMIServer(PORT, HISTORY_FILENAME);
            else
                chatServer = new SocketServer(PORT, HISTORY_FILENAME);
            chatServer.run();
        } catch (Exception e) {
            System.err.println("FATAL: " + e.toString());
            e.printStackTrace();
        }
    }

}
