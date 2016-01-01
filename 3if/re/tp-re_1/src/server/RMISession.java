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

    @Override
    public boolean isActive() {
        try {
            client.ping();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    @Override
    public void sendHistory(LinkedList<String> messages) {
        try {
            client.sendHistory(messages);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage history"
            );
        }
    }

    @Override
    public void sendMessage(String date, String message) {
        try {
            client.sendMessage(date, message);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage message (" + e.getMessage() + ")"
            );
        }
    }

    @Override
    public void sendPrivateMessage(
            String date, String username, String message)
    {
        try {
            client.sendPrivateMessage(date, username, message);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage PM (" + e.getMessage() + ")"
            );
        }
    }

    @Override
    public void sendUserList(String[] users) {
        try {
            client.sendUserList(users);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage list user (" + e.getMessage() + ")"
            );
        }
    }

}
