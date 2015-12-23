package server;

import java.io.*;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.regex.Pattern;

import server.exceptions.*;

abstract class Server {

    final static private String DATE_FORMAT = "[HH:mm:ss]";
    final static private Pattern USERNAME_PATTERN = Pattern.compile(
            "^[a-zA-Z0-9_\\-]{3,32}$"
    );

    protected final int port;

    private BufferedWriter historyBufferedWriter;

    private final LinkedList<String> messages = new LinkedList<>();
    private final HashMap<String, Session> sessions = new HashMap<>();
    private final SecureRandom random = new SecureRandom();
    private final SimpleDateFormat dateFormatter =
            new SimpleDateFormat(DATE_FORMAT);

    public Server(int serverPort, String historyFilename) throws IOException {
        super();
        port = serverPort;
        File historyFile = new File(historyFilename);
        loadMessageHistory(historyFile);
        FileWriter historyFileWriter = new FileWriter(historyFile, true);
        historyBufferedWriter = new BufferedWriter(historyFileWriter);
    }

    public abstract void run() throws Exception;

    protected void addMessage(String sessionId, String message)
            throws InvalidSessionException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        String username = sessions.get(sessionId).getUsername();
        broadcastMessage("<" + username + "> " + message);
    }

    protected void addPrivateMessage(
            String sessionId, String destUsername, String message)
            throws InvalidSessionException, UserNotFoundException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        Session srcSession = sessions.get(sessionId);
        Session destSession = getSessionByUsername(destUsername);
        if (checkSessionActive(destSession))
            destSession.sendPrivateMessage(srcSession.getUsername(), message);
        else
            throw new UserNotFoundException();
    }

    protected String addUser(Session session)
            throws InvalidUsernameException {
        if (!isUsernameAvailable(session.getUsername()))
            throw new InvalidUsernameException();
        String sessionId = registerSession(session);
        session.sendHistory(messages);
        broadcastUserList();
        broadcastMessage("* " + session.getUsername() + " has joined *");
        return sessionId;
    }

    protected void removeUser(String sessionId)
            throws InvalidSessionException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        String username = sessions.get(sessionId).getUsername();
        broadcastMessage("* " + username + " has left *");
        sessions.remove(sessionId);
        broadcastUserList();
    }

    protected void renameUser(String sessionId, String newUsername)
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

    private void broadcastMessage(String message) {
        Date now = new Date();
        String line = dateFormatter.format(now) + " " + message;
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
        for (Session session : sessions.values())
            if (checkSessionActive(session))
                session.sendMessage(line);
    }

    private void broadcastUserList() {
        String[] userList = getUserList();
        for (Session session : sessions.values())
            if (checkSessionActive(session))
                session.sendUserList(userList);
    }

    private boolean checkSessionActive(Session session) {
        if (session != null) {
            if (session.isActive())
                return true;
            sessions.values().remove(session);
            broadcastUserList();
            broadcastMessage(
                    "* " + session.getUsername() + " has been disconnected *"
            );
        }
        return false;
    }

    private boolean checkSessionExists(String sessionId) {
        return sessions.containsKey(sessionId);
    }

    private Session findSession(String username) {
        for (Session session : sessions.values()) {
            if (!checkSessionActive(session))
                continue;
            if (session.getUsername().equals(username))
                return session;
        }
        return null;
    }

    private String getNextSessionId() {
        return new BigInteger(130, random).toString(32);
    }

    private Session getSessionByUsername(String username) {
        for (Session session : sessions.values()) {
            if (session.getUsername().equals(username))
                return session;
        }
        return null;
    }

    private String[] getUserList() {
        String[] users = new String[sessions.size()];
        int i = 0;
        for (Session session : sessions.values()) {
            if (!checkSessionActive(session))
                continue;
            users[i] = session.getUsername();
            i++;
        }
        return users;
    }

    private boolean isUsernameAvailable(String username) {
        return isUsernameValid(username) && findSession(username) == null;
    }

    private void loadMessageHistory(File historyFile) throws IOException {
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

    private String registerSession(Session session) {
        String sessionId = getNextSessionId();
        sessions.put(sessionId, session);
        return sessionId;
    }

    private static boolean isUsernameValid(String username) {
        return USERNAME_PATTERN.matcher(username).find();
    }
}
