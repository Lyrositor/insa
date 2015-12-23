package server;

import protocol.RMIClientInterface;

import java.util.LinkedList;

class RMISession extends Session {

    private final RMIClientInterface client;

    public RMISession(
            String sessionUsername, RMIClientInterface sessionClient
    ) {
        super(sessionUsername);
        client = sessionClient;
    }

    public boolean isActive() {
        try {
            client.ping();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    public void sendHistory(LinkedList<String> messages) {

    }

    public void sendMessage(String message) {
        try {
            client.send(message);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to send message (" + e.getMessage() + ")"
            );
        }
    }

    public void sendPrivateMessage(String username, String message) {

    }

    public void sendUserList(String[] users) {
        try {
            client.sendUserList(users);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to send list user (" + e.getMessage() + ")"
            );
        }
    }

}
