package marno.server.exceptions;

import marno.protocol.MarnoProtocol;

/**
 * Exception thrown when a client-provided username is invalid for some reason.
 */
public class InvalidUsernameException extends ServerException {

    /**
     * Constructs a new exception with null as its detail message.
     */
    public InvalidUsernameException() {
        super();
    }

    /**
     * Returns the error code specific to this exception.
     *
     * @return the numeric error code for this exception
     */
    @Override
    public int getCode() {
        return MarnoProtocol.INVALID_USERNAME;
    }

}

