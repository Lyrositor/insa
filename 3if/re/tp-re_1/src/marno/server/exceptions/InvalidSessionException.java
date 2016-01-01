package marno.server.exceptions;

import marno.protocol.MarnoProtocol;

/**
 * Exception thrown when a session ID does not correspond to a valid session.
 */
public class InvalidSessionException extends ServerException {

    /**
     * Constructs a new exception with null as its detail message.
     */
    public InvalidSessionException() {
        super();
    }

    /**
     * Returns the error code specific to this exception.
     *
     * @return the numeric error code for this exception
     */
    @Override
    public int getCode() {
        return MarnoProtocol.INVALID_SESSION;
    }

}
