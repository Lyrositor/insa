package server.exceptions;

import protocol.MarnoProtocol;

public class InvalidUsernameException extends ServerException {

    public InvalidUsernameException() {
        super();
    }

    public InvalidUsernameException(Throwable throwable) {
        super(throwable);
    }

    public int getCode() {
        return MarnoProtocol.INVALID_USERNAME;
    }

}

