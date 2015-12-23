package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.LinkedList;

import server.exceptions.*;

class SocketSession extends Session implements Runnable {

    private final Socket client;
    private final SocketServer server;
    private String sessionId;
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

    public boolean isActive() {
        return true;
    }

    public void run() {
        for (;;) {
            String line;
            try {
                line = socketIn.readLine();
            } catch (IOException e) {
                System.out.println("CLIENT: Closing socket with client");
                break;
            }
            handleInput(line);
        }
    }

    public void sendHistory(LinkedList<String> messages) {
        socketOut.print("HISTORY");
        for (String message : messages)
            socketOut.printf(" %d %s", message.length(), message);
        socketOut.println();
    }

    public void sendMessage(String message) {
        socketOut.println("MSG " + message);
    }

    public void sendPrivateMessage(String username, String message) {
        socketOut.println("PRIVATE " + username + " " + message);
    }

    public void sendUserList(String[] users) {
        socketOut.println("USERS " + String.join(" ", users));
    }

    private void handleInput(String input) {
        String[] command = input.split(" ", 2);
        System.out.println("CLIENT: " + input);
        try {
            switch (command[0]) {
                case "CONNECT":
                    changeUsername(command[1]);
                    sessionId = server.addUser(this);
                    break;

                case "MSG":
                    server.addMessage(sessionId, command[1]);
                    break;

                case "PRIVATE":
                    try {
                        server.addPrivateMessage(sessionId, command[1], command[2]);
                    } catch (UserNotFoundException e) {
                        sendError(e.getCode(), command[1]);
                    }
                    break;

                case "RENAME":
                    server.renameUser(sessionId, command[1]);
                    break;

                case "DISCONNECT":
                    server.removeUser(sessionId);
                    try {
                        socketIn.close();
                        socketOut.close();
                    } catch (IOException e) {
                        System.err.println(
                                "ERROR: Failed to close client socket");
                    }
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
}
