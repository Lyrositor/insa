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

    public abstract boolean isActive();

    public abstract void sendHistory(LinkedList<String> messages);

    public abstract void sendMessage(String message);

    public abstract void sendPrivateMessage(String username, String message);

    public abstract void sendUserList(String[] users);

}
