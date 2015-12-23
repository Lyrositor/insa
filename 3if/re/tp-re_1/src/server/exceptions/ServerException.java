package server.exceptions;

public abstract class ServerException extends Exception {

    public ServerException() {
        super();
    }

    public ServerException(Throwable throwable) {
        super(throwable);
    }

    public abstract int getCode();
}
