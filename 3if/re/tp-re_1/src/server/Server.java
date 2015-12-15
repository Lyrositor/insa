package server;

import java.io.*;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.text.SimpleDateFormat;
import java.util.*;

abstract class Server {

    final static private String dateFormat = "[HH:mm:ss]";

    protected int port;

    private BufferedWriter historyBufferedWriter;
    private LinkedList<String> messages = new LinkedList<>();
    private HashMap<String, Session> sessions = new HashMap<>();

    private SecureRandom random = new SecureRandom();
    private SimpleDateFormat dateFormatter = new SimpleDateFormat(dateFormat);

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
            throws IOException {
        if (!checkSessionExists(sessionId))
            throw new RuntimeException("Invalid session ID");
        String username = sessions.get(sessionId).getUsername();
        broadcastMessage("<" + username + "> " + message);
    }

    protected String addUser(Session session) {
        if (!checkUsername(session.getUsername()))
            throw new RuntimeException("Username already in use");
        String sessionId = registerSession(session);
        session.sendMessages(messages);
        broadcastUserList();
        broadcastMessage("* " + session.getUsername() + " has joined *");
        return sessionId;
    }

    protected void removeUser(String sessionId) {
        if (!checkSessionExists(sessionId))
            throw new RuntimeException("Invalid session ID");
        String username = sessions.get(sessionId).getUsername();
        broadcastMessage("* " + username + " has left *");
        sessions.remove(sessionId);
        broadcastUserList();
    }

    protected void renameUser(String sessionId, String newUsername) {
        if (!checkSessionExists(sessionId))
            throw new RuntimeException("Invalid session ID");
        if (!checkUsername(newUsername))
            throw new RuntimeException("Username already in use");
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
        if (session.isActive())
            return true;
        sessions.values().remove(session);
        broadcastUserList();
        broadcastMessage(
                "* " + session.getUsername() + " has been disconnected *"
        );
        return false;
    }

    private boolean checkSessionExists(String sessionId) {
        return sessions.containsKey(sessionId);
    }

    private boolean checkUsername(String username) {
        for (Session session : sessions.values()) {
            if (!checkSessionActive(session))
                continue;
            if (session.getUsername().equals(username))
                return false;
        }
        return true;
    }

    private String getNextSessionId() {
        return new BigInteger(130, random).toString(32);
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
}
