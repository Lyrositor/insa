package marno.server;

import java.io.*;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.regex.Pattern;

import marno.server.exceptions.*;

/**
 * Handles server functionality that is independent of the underlying protocol
 * implementation (RMI or sockets).
 */
abstract class Server {

    /**
     * The format for message timestamps.
     */
    final static private String DATE_FORMAT = "[HH:mm:ss]";

    /**
     * The pattern usernames must match against to be considered valid.
     */
    final static private Pattern USERNAME_PATTERN = Pattern.compile(
            "^[a-zA-Z0-9_\\-]{3,32}$"
    );

    /**
     * The port the server is listening on.
     */
    protected final int port;

    /**
     * The writer to the message history file.
     */
    private BufferedWriter historyBufferedWriter;

    /**
     * The list of messages that have been added so far.
     *
     * Each message here includes its prepended timestamp.
     */
    private final LinkedList<String> messages = new LinkedList<>();

    /**
     * A hash map of sessions associated with a session ID string.
     */
    private final HashMap<String, Session> sessions = new HashMap<>();

    /**
     * The secure random value generator.
     */
    private final SecureRandom random = new SecureRandom();

    /**
     * The timestamp formatter, for each message.
     */
    private final SimpleDateFormat dateFormatter =
            new SimpleDateFormat(DATE_FORMAT);

    /**
     * Prepares the server, loading previous messages from the history file.
     *
     * @param serverPort the port on which to listen for client connections
     * @param historyFilename the filename for the message history file to open
     * @throws IOException if the history file could not be opened
     */
    public Server(int serverPort, String historyFilename) throws IOException {
        port = serverPort;
        File historyFile = new File(historyFilename);
        loadMessageHistory(historyFile);
        FileWriter historyFileWriter = new FileWriter(historyFile, true);
        historyBufferedWriter = new BufferedWriter(historyFileWriter);
    }

    /**
     * Makes the server run indifinitely.
     *
     * @throws Exception if an exception occurs during execution
     */
    public abstract void run() throws Exception;

    /**
     * Adds a new message to the list of received messages, then broadcasts it
     * to all clients.
     *
     * @param sessionId the ID of the client's session, for authentication
     * @param message the client's message contents
     * @throws InvalidSessionException if the session ID is invalid
     */
    protected synchronized void addMessage(String sessionId, String message)
            throws InvalidSessionException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        String username = sessions.get(sessionId).getUsername();
        broadcastMessage("<" + username + "> " + message);
    }

    /**
     * Relays a private message from one user to another, by username.
     *
     * @param sessionId the ID of the client's session, for authentication
     * @param destUsername the username of the intended recipient
     * @param message the client's message contents
     * @throws InvalidSessionException if the session ID is invalid
     * @throws UserNotFoundException if the specified username was not found
     */
    protected synchronized void addPrivateMessage(
            String sessionId, String destUsername, String message)
            throws InvalidSessionException, UserNotFoundException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        String destSessionId = getSessionIdByUsername(destUsername);
        Session srcSession = sessions.get(sessionId);
        Session destSession = sessions.get(destSessionId);
        if (checkSessionActive(destSessionId))
            destSession.sendPrivateMessage(
                    dateFormatter.format(new Date()),
                    srcSession.getUsername(),
                    message
            );
        else
            throw new UserNotFoundException();
    }

    /**
     * Adds a new user with its own session associated.
     *
     * Only succeeds if no other user has that username and if the username
     * contains only alphanumeric characters, '-' and '_'. On success,
     * broadcasts a status message notifying clients that a new user has joined.
     *
     * @param session the new session to add
     * @return the newly-added session's unique ID
     * @throws InvalidUsernameException if the username is taken or contains
     * invalid characters
     */
    protected synchronized String addUser(Session session)
            throws InvalidUsernameException {
        if (!isUsernameAvailable(session.getUsername()))
            throw new InvalidUsernameException();
        String sessionId = registerSession(session);
        session.sendHistory(messages);
        broadcastUserList();
        broadcastMessage("* " + session.getUsername() + " has joined *");
        return sessionId;
    }

    /**
     * Removes a user from the list of active users.
     *
     * On success, broadcasts a status message notifying clients that a user has
     * left.
     *
     * @param sessionId the ID of the client's session, for authentication
     * @throws InvalidSessionException if the session ID is invalid
     */
    protected synchronized void removeUser(String sessionId)
            throws InvalidSessionException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        String username = sessions.get(sessionId).getUsername();
        sessions.remove(sessionId);
        broadcastMessage("* " + username + " has left *");
        broadcastUserList();
    }

    /**
     * Changes a user's username to a new value, if the new value is valid.
     *
     * On success, broadcasts a status message notifying clients that a user has
     * changed their username.
     *
     * @param sessionId the ID of the client's session, for authentication
     * @param newUsername the new value for the client's username
     * @throws InvalidSessionException if the session ID is invalid
     * @throws InvalidUsernameException if the username is taken or contains
     * invalid characters
     */
    protected synchronized void renameUser(String sessionId, String newUsername)
            throws InvalidSessionException, InvalidUsernameException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        if (!isUsernameAvailable(newUsername))
            throw new InvalidUsernameException();
        Session session = sessions.get(sessionId);
        String oldUsername = session.getUsername();
        session.changeUsername(newUsername);
        broadcastUserList();
        broadcastMessage(
                "* " + oldUsername + " is now known as " + newUsername + " *"
        );
    }

    /**
     * Broadcasts a message publicly to all clients.
     *
     * Each message is prepended with a timestamp.
     *
     * @param message the message's contents
     */
    private synchronized void broadcastMessage(String message) {
        String now = dateFormatter.format(new Date());
        String line = now + " " + message;
        messages.add(line);
        try {
            historyBufferedWriter.write(line);
            historyBufferedWriter.newLine();
            historyBufferedWriter.flush();
        } catch (IOException e) {
            System.err.println(
                    "ERROR: Failed to write to history file (" + e.getMessage()
                            + ")"
            );
        }
        for (Map.Entry<String, Session> s : sessions.entrySet())
            if (checkSessionActive(s.getKey()))
                s.getValue().sendMessage(now, message);
    }

    /**
     * Broadcasts the current list of usernames to all clients.
     */
    private synchronized void broadcastUserList() {
        String[] userList = getUserList();
        for (Map.Entry<String, Session> s : sessions.entrySet())
            if (checkSessionActive(s.getKey()))
                s.getValue().sendUserList(userList);
    }

    /**
     * Checks that the specified session is still active.
     *
     * A session is considered active if it can respond in a timely manner to
     * pings. If it is no longer active, it is removed.
     *
     * @param sessionId the ID of the session to check
     * @return true if the session is active, false otherwise
     */
    private synchronized boolean checkSessionActive(String sessionId) {
        Session session = sessions.get(sessionId);
        if (session != null) {
            if (session.isActive())
                return true;
            try {
                removeUser(sessionId);
            } catch (InvalidSessionException e) {
                e.printStackTrace();
            }
        }
        return false;
    }

    /**
     * Checks that a session has been registered with the specified ID.
     *
     * @param sessionId the ID of the session to check
     * @return true if such a session was found, false otherwise
     */
    private synchronized boolean checkSessionExists(String sessionId) {
        return sessions.containsKey(sessionId);
    }

    /**
     * Attempts to find a session associated with a specific username.
     *
     * @param username the username to search for
     * @return the session if found, {@code null} otherwise
     */
    private synchronized Session findSession(String username) {
        for (Map.Entry<String, Session> s : sessions.entrySet()) {
            if (!checkSessionActive(s.getKey()))
                continue;
            if (s.getValue().getUsername().equals(username))
                return s.getValue();
        }
        return null;
    }

    /**
     * Gets a new unique session ID for a new session.
     *
     * @return a new randomly-generated string ID
     */
    private synchronized String getNextSessionId() {
        return new BigInteger(130, random).toString(32);
    }

    /**
     * Finds the session ID associated with a specific username.
     *
     * @param username the username to search for
     * @return the session ID if found, {@code null} otherwise
     */
    private synchronized String getSessionIdByUsername(String username) {
        for (Map.Entry<String, Session> s : sessions.entrySet()) {
            if (s.getValue().getUsername().equals(username))
                return s.getKey();
        }
        return null;
    }

    /**
     * Returns a sorted list of users.
     *
     * @return the sorted list of users on the server
     */
    private synchronized String[] getUserList() {
        String[] users = new String[sessions.size()];
        int i = 0;
        for (Map.Entry<String, Session> s : sessions.entrySet()) {
            if (!checkSessionActive(s.getKey()))
                continue;
            users[i] = s.getValue().getUsername();
            i++;
        }
        Arrays.sort(users);
        return users;
    }

    /**
     * Checks if a username has not been taken by another user and if it is a
     * valid username.
     *
     * @param username the username to check
     * @return true if the username is valid and not in use, false otherwise
     */
    private synchronized boolean isUsernameAvailable(String username) {
        return isUsernameValid(username) && findSession(username) == null;
    }

    /**
     * Loads all previous messages from the history file.
     *
     * @param historyFile the file to load messages from, ready to be read
     * @throws IOException if the file could not be opened
     */
    private synchronized void loadMessageHistory(File historyFile)
            throws IOException {
        if (historyFile.createNewFile())
            return;
        FileReader reader = new FileReader(historyFile);
        BufferedReader bufferedReader = new BufferedReader(reader);
        String line;
        while((line = bufferedReader.readLine()) != null) {
            if (!line.isEmpty())
                messages.add(line);
        }
        bufferedReader.close();
    }

    /**
     * Registers a new session with the server, associating it a unique ID.
     *
     * @param session the session to register
     * @return the session ID of the newly-registered session
     */
    private synchronized String registerSession(Session session) {
        String sessionId = getNextSessionId();
        sessions.put(sessionId, session);
        return sessionId;
    }

    /**
     * Checks if a username matches all the criteria on usernames.
     *
     * @param username the username to check
     * @return true if it is valid, false otherwise
     */
    private static boolean isUsernameValid(String username) {
        return USERNAME_PATTERN.matcher(username).find();
    }
}
