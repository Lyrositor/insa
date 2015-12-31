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

    protected synchronized void addMessage(String sessionId, String message)
            throws InvalidSessionException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        String username = sessions.get(sessionId).getUsername();
        broadcastMessage("<" + username + "> " + message);
    }

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
                    dateFormatter.format(
                            new Date()) + " " + srcSession.getUsername(), 
                    message);
        else
            throw new UserNotFoundException();
    }

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

    protected synchronized void removeUser(String sessionId)
            throws InvalidSessionException {
        if (!checkSessionExists(sessionId))
            throw new InvalidSessionException();
        String username = sessions.get(sessionId).getUsername();
        sessions.remove(sessionId);
        broadcastMessage("* " + username + " has left *");
        broadcastUserList();
    }

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

    private synchronized void broadcastMessage(String message) {
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
        for (Map.Entry<String, Session> s : sessions.entrySet())
            if (checkSessionActive(s.getKey()))
                s.getValue().sendMessage(line);
    }

    private synchronized void broadcastUserList() {
        String[] userList = getUserList();
        for (Map.Entry<String, Session> s : sessions.entrySet())
            if (checkSessionActive(s.getKey()))
                s.getValue().sendUserList(userList);
    }

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

    private synchronized boolean checkSessionExists(String sessionId) {
        return sessions.containsKey(sessionId);
    }

    private synchronized Session findSession(String username) {
        for (Map.Entry<String, Session> s : sessions.entrySet()) {
            if (!checkSessionActive(s.getKey()))
                continue;
            if (s.getValue().getUsername().equals(username))
                return s.getValue();
        }
        return null;
    }

    private synchronized String getNextSessionId() {
        return new BigInteger(130, random).toString(32);
    }

    private synchronized String getSessionIdByUsername(String username) {
        for (Map.Entry<String, Session> s : sessions.entrySet()) {
            if (s.getValue().getUsername().equals(username))
                return s.getKey();
        }
        return null;
    }

    private synchronized String[] getUserList() {
        String[] users = new String[sessions.size()];
        int i = 0;
        for (Map.Entry<String, Session> s : sessions.entrySet()) {
            if (!checkSessionActive(s.getKey()))
                continue;
            users[i] = s.getValue().getUsername();
            i++;
        }
        return users;
    }

    private synchronized boolean isUsernameAvailable(String username) {
        return isUsernameValid(username) && findSession(username) == null;
    }

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

    private synchronized String registerSession(Session session) {
        String sessionId = getNextSessionId();
        sessions.put(sessionId, session);
        return sessionId;
    }

    private static boolean isUsernameValid(String username) {
        return USERNAME_PATTERN.matcher(username).find();
    }
}
