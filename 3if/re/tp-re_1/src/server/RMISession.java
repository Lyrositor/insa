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

    public void sendMessage(String message) {
        try {
            client.Send(message);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to send message (" + e.getMessage() + ")"
            );
        }
    }

    public void sendMessages(String[] messages, boolean compressed) {

    }

    public void sendUserList(String[] users) {

    }

}
