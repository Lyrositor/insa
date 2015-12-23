package server.exceptions;

import protocol.MarnoProtocol;

public class InvalidSessionException extends ServerException {

    public InvalidSessionException() {
        super();
    }

    public InvalidSessionException(Throwable throwable) {
        super(throwable);
    }

    public int getCode() {
        return MarnoProtocol.INVALID_SESSION;
    }

}
