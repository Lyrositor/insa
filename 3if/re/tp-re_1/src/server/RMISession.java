package server;

import protocol.ClientRMIInterface;

public class RMISession extends Session {

    private ClientRMIInterface client;

    public RMISession(
            String sessionUsername, ClientRMIInterface sessionClient
    ) {
        super(sessionUsername);
        client = sessionClient;
    }

    public boolean isActive() {
        try {
            client.Ping();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    public void sendMessage(String message) {
        try {
            client.Send(message);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to send message (" + e.getMessage() + ")"
            );
        }
    }

    public void sendUserList(String[] users) {

    }

}
