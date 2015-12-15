package server;

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

    public abstract void sendMessages(String[] messages, boolean compressed);

    public abstract void sendMessage(String message);

    public abstract void sendUserList(String[] users);
}
