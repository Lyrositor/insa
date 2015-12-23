package server.exceptions;

import protocol.MarnoProtocol;

public class UserNotFoundException extends ServerException {

    public UserNotFoundException() {
        super();
    }

    public UserNotFoundException(Throwable throwable) {
        super(throwable);
    }

    public int getCode() {
        return MarnoProtocol.USER_NOT_FOUND;
    }

}
