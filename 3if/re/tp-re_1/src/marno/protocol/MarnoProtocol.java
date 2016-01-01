package marno.protocol;

/**
 * Common definitions for the socket-based Marno protocol.
 */
public class MarnoProtocol {

    /**
     * The frequency at which the client should ping the server.
     */
    public static final int PING_FREQUENCY = 1000;

    /**
     * The limit of time to let pass before a client is disconnected from the
     * server, or before the client decides the server is gone.
     */
    public static final int TIMEOUT = 5000;

    /**
     * Error code for an invalid session ID.
     */
    public static final int INVALID_SESSION = 0;

    /**
     * Error code for an invalid username (either because it contains invalid
     * characters or because it is already taken).
     */
    public static final int INVALID_USERNAME = 1;

    /**
     * Error code for when a user was not found on the server.
     */
    public static final int USER_NOT_FOUND = 2;

    /**
     * Human-readable error messages for the clients.
     */
    public static final String[] ERROR_MESSAGES = {
            "Invalid session ID. Client is not registered with server.",
            "Invalid username.",
            "Username %s could not be found."
    };

}
