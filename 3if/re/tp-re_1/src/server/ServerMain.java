package server;

public class ServerMain {

    final static private String HISTORY_FILENAME = "ChatMarcArno.log";
    final static private int PORT = 1099;

    public static void main(String args[]) {
        Server chatServer;

        boolean useRMI = true;

        try {
            if (useRMI)
                chatServer = new RMIServer(PORT, HISTORY_FILENAME);
            else
                return;
            chatServer.run();
        } catch (Exception e) {
            System.err.println("[Server exception]: " + e.toString());
            e.printStackTrace();
        }
    }

}
