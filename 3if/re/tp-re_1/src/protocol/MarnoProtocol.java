package protocol;

public class MarnoProtocol {

    public static final int PING_FREQUENCY = 1000;
    public static final int TIMEOUT = 5000;

    public static final int INVALID_SESSION = 0;
    public static final int INVALID_USERNAME = 1;
    public static final int USER_NOT_FOUND = 2;

    public static final String[] ERROR_MESSAGES = {
            "Invalid session ID. Client is not registered with server.",
            "Invalid username.",
            "Username %s could not be found."
    };

}
