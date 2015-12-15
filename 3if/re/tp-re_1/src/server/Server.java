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

    protected void addMessage(String sessionId, String message) throws IOException {
        if (!checkSession(sessionId))
            throw new RuntimeException("Invalid session ID");
        Date now = new Date();
        String username = sessions.get(sessionId).getUsername();
        String line =
                dateFormatter.format(now) + " <" + username + "> " + message;
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
        broadcastMessage(line);
    }

    protected String addUser(Session session) {
        if (!checkUsername(session.getUsername()))
            throw new RuntimeException("Username already in use");
        String sessionId = registerSession(session);
        session.sendMessages(messages);
        broadcastUserList();
        return sessionId;
    }

    protected void removeUser(String sessionId) {
        if (!checkSession(sessionId))
            throw new RuntimeException("Invalid session ID");
        sessions.remove(sessionId);
        broadcastUserList();
    }

    protected void renameUser(String sessionId, String newUsername) {
        if (!checkSession(sessionId))
            throw new RuntimeException("Invalid session ID");
        if (!checkUsername(newUsername))
            throw new RuntimeException("Username already in use");
        sessions.get(sessionId).changeUsername(newUsername);
    }

    private void broadcastMessage(String message) {
        for (Session session : sessions.values())
            session.sendMessage(message);
    }

    private void broadcastUserList() {
        String[] userList = getUserList();
        for (Session session : sessions.values())
            session.sendUserList(userList);
    }

    private boolean checkSession(String sessionId) {
        return sessions.containsKey(sessionId);
    }

    private boolean checkUsername(String username) {
        for (Session value : sessions.values())
            if ((value).getUsername().equals(username))
                return false;
        return true;
    }

    private String getNextSessionId() {
        return new BigInteger(130, random).toString(32);
    }

    private String[] getUserList() {
        String[] users = new String[sessions.size()];
        int i = 0;
        for (Session session : sessions.values()) {
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
