package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.LinkedList;

import server.exceptions.*;

class SocketSession extends Session implements Runnable {

    private boolean isActive = true;
    private String sessionId;

    private final Socket client;
    private final SocketServer server;
    private final BufferedReader socketIn;
    private final PrintStream socketOut;

    public SocketSession(SocketServer clientServer, Socket clientSocket)
            throws IOException {
        super("");
        client = clientSocket;
        server = clientServer;

        socketIn = new BufferedReader(new InputStreamReader(
                client.getInputStream()));
        socketOut = new PrintStream(client.getOutputStream(), true);
    }

    @Override
    public boolean isActive() {
        return isActive;
    }

    @Override
    public void run() {
        while (isActive) {
            String line;
            try {
                line = socketIn.readLine();
            } catch (IOException e) {
                System.out.println("INFO: Closing socket with client");
                try {
                    disconnect();
                } catch (ServerException se) {
                    System.out.println("ERROR: Failed to disconnect properly");
                }
                break;
            }
            handleInput(line);
        }
    }

    @Override
    public void sendHistory(LinkedList<String> messages) {
        socketOut.print("HISTORY " + messages.size());
        for (String message : messages)
            socketOut.printf(" %d %s", message.length(), message);
        socketOut.println();
    }

    @Override
    public void sendMessage(String date, String message) {
        socketOut.println("MSG " + date + " " + message);
    }

    @Override
    public void sendPrivateMessage(
            String date, String username, String message
    ) {
        socketOut.println("PRIVATE " + date + " " + username + " " + message);
    }

    @Override
    public void sendUserList(String[] users) {
        socketOut.println("USERS " + String.join(" ", users));
    }

    private void handleInput(String input) {
        String[] command = input.split(" ", 2);
        String[] subCommand;
        isActive = true;
        System.out.println("CLIENT: " + input);
        try {
            switch (command[0]) {
                case "CONNECT":
                    changeUsername(command[1]);
                    sessionId = server.addUser(this);
                    break;

                case "PING":
                    socketOut.println("PONG");
                    break;

                case "MSG":
                    server.addMessage(sessionId, command[1]);
                    break;

                case "PRIVATE":
                    subCommand = command[1].split(" ", 2);
                    try {
                        server.addPrivateMessage(sessionId, subCommand[0], subCommand[1]);
                    } catch (UserNotFoundException e) {
                        sendError(e.getCode(), command[1]);
                    }
                    break;

                case "RENAME":
                    server.renameUser(sessionId, command[1]);
                    break;

                case "DISCONNECT":
                    disconnect();
                    break;

                default:
                    System.err.println("ERROR: Invalid command");
            }
        } catch (ServerException e) {
            sendError(e.getCode());
        }
    }

    private void sendError(int errorCode, String... arguments) {
        if (arguments.length > 0)
            socketOut.printf(
                    "ERROR %d %s", errorCode, String.join(" ", arguments));
        else
            socketOut.print("ERROR " + errorCode);
        socketOut.println();
    }

    private void disconnect() throws ServerException {
        isActive = false;
        server.removeUser(sessionId);
        try {
            socketIn.close();
            socketOut.close();
        } catch (IOException e) {
            System.err.println(
                    "ERROR: Failed to close client socket");
        }
    }
}
