package marno.server.exceptions;

/**
 * Base class for exceptions thrown by the server.
 *
 * Each server exception should have an associated error code, defined in
 * {@code marno.protocol.MarnoProtocol}
 */
public abstract class ServerException extends Exception {

    /**
     * Constructs a new exception with null as its detail message.
     */
    public ServerException() {
        super();
    }

    /**
     * Returns the error code specific to this exception.
     *
     * @return the numeric error code for this exception
     */
    public abstract int getCode();
}
