package marno.server.exceptions;

import marno.protocol.MarnoProtocol;

/**
 * Exception thrown when a user with a certain username could not be found.
 */
public class UserNotFoundException extends ServerException {

    /**
     * Constructs a new exception with null as its detail message.
     */
    public UserNotFoundException() {
        super();
    }

    /**
     * Returns the error code specific to this exception.
     *
     * @return the numeric error code for this exception
     */
    @Override
    public int getCode() {
        return MarnoProtocol.USER_NOT_FOUND;
    }

}
