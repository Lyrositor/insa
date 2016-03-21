package marno.server;

import java.util.LinkedList;

/**
 * Represents a connected client.
 */
abstract class Session {

    /**
     * The client's username.
     */
    private String username;

    /**
     * Creates a new session tied to the specified username.
     *
     * @param sessionUsername the client's username
     */
    public Session(String sessionUsername) {
        username = sessionUsername;
    }

    /**
     * Changes the client's username to a new value.
     *
     * @param newUsername the new username value
     */
    public void changeUsername(String newUsername) {
        username = newUsername;
    }

    /**
     * Gets the client's current username.
     *
     * @return the current username
     */
    public String getUsername() {
        return username;
    }

    /**
     * Checks if a session is still considered active.
     *
     * @return true if it is active, false otherwise
     */
    public abstract boolean isActive();

    /**
     * Sends a history of messages to the client.
     *
     * @param messages the list of messages to send
     */
    public abstract void sendHistory(LinkedList<String> messages);

    /**
     * Relays a public message to the client.
     *
     * @param date the date on which the message was received
     * @param message the contents of the message
     */
    public abstract void sendMessage(
            String date, String message);

    /**
     * Relays a private message from another user to the client.
     *
     * @param date the date on which the message was received
     * @param username the source of the message
     * @param message the contents of the message
     */
    public abstract void sendPrivateMessage(
            String date, String username, String message);

    /**
     * Sends a sorted list of users to the client.
     *
     * @param users the list of users currently on the server
     */
    public abstract void sendUserList(String[] users);

}
