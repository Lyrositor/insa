package server;

import java.util.LinkedList;

abstract class Session {
    private String username;

    public Session(String sessionUsername) {
        username = sessionUsername;
    }

    public void changeUsername(String newUsername) {
        username = newUsername;
    }

    public String getUsername() {
        return username;
    }

    public void sendMessages(LinkedList<String> messages) {
        String joinedMessage = String.join("\n", messages);
        try {
            sendMessage(joinedMessage);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to send message (" + e.getMessage() + ")"
            );
        }
    }

    public abstract void sendMessage(String message);

    public abstract void sendUserList(String[] users);
}
