package server;

public class ServerMain {

    final static private String HISTORY_FILENAME = "ChatMarcArno.log";
    final static private int PORT = 1099;

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
