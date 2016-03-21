package marno.server;

import marno.protocol.RMIClientInterface;

import java.util.LinkedList;

/**
 * Represents a connected RMI client.
 */
class RMISession extends Session {

    /**
     * The RMI client bound to the session.
     */
    private final RMIClientInterface client;

    /**
     * Constructs a new RMI session with a connected client.
     *
     * @param sessionUsername the username of the client
     * @param sessionClient the RMI client remote object
     */
    public RMISession(String sessionUsername, RMIClientInterface sessionClient)
    {
        super(sessionUsername);
        client = sessionClient;
    }

    /**
     * Checks whether the client is still connected and responding.
     *
     * @return true if the client can be reached, false otherwise
     */
    @Override
    public boolean isActive() {
        try {
            client.ping();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    /**
     * Sends a grouped history of all previous chat messages to the client.
     *
     * @param history a list of past messages
     */
    @Override
    public void sendHistory(LinkedList<String> history) {
        try {
            client.sendHistory(history);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage history"
            );
        }
    }

    /**
     * Sends a public message to the client.
     *
     * @param date the date/time on which the message was received
     * @param message the contents of the message
     */
    @Override
    public void sendMessage(String date, String message) {
        try {
            client.sendMessage(date, message);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage message (" + e.getMessage() +
                    ")"
            );
        }
    }

    /**
     * Sends a private message to the client.
     *
     * @param date the date/time on which the message was received
     * @param username the username of the sender of the private message
     * @param message the contents of the message
     */
    @Override
    public void sendPrivateMessage(String date, String username, String message)
    {
        try {
            client.sendPrivateMessage(date, username, message);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage PM (" + e.getMessage() + ")"
            );
        }
    }

    /**
     * Sends a list of all connected users to the client.
     *
     * @param users the list of users
     */
    @Override
    public void sendUserList(String[] users) {
        try {
            client.sendUserList(users);
        } catch (Exception e) {
            System.err.println(
                    "ERROR: Failed to sendMessage list user (" + e.getMessage()
                    + ")"
            );
        }
    }

}
