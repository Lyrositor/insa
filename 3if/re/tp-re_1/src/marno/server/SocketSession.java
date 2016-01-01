package marno.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.LinkedList;

import marno.server.exceptions.*;

/**
 * Represents a connected socket client.
 */
class SocketSession extends Session implements Runnable {

    /**
     * The current status of the session.
     */
    private boolean isActive = true;

    /**
     * The unique ID of the session.
     */
    private String sessionId;

    /**
     * The client socket associated with this session.
     */
    private final Socket client;

    /**
     * The socket server hosting this session.
     */
    private final SocketServer server;

    /**
     * The client socket input reader.
     */
    private final BufferedReader socketIn;

    /**
     * The client socket output writer.
     */
    private final PrintStream socketOut;

    /**
     * Constructs a new session tied to a socket connection and a server.
     *
     * @param clientServer the server hosting the session
     * @param clientSocket the client socket from the incoming connection
     * @throws IOException if the client socket could not be read
     */
    public SocketSession(SocketServer clientServer, Socket clientSocket)
            throws IOException {
        super("");
        client = clientSocket;
        server = clientServer;

        socketIn = new BufferedReader(new InputStreamReader(
                client.getInputStream()));
        socketOut = new PrintStream(client.getOutputStream(), true);
    }

    /**
     * Checks if this session is still active.
     *
     * A socket session is considered inactive if its client has not sent any
     * messages in the past few seconds.
     *
     * @return true if still active, false otherwise
     */
    @Override
    public boolean isActive() {
        return isActive;
    }

    /**
     * Runs while the socket can still be read from or until the client quits.
     */
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

    /**
     * Sends a history of all past messages to the client.
     *
     * Format: {@code HISTORY <num> <len1> <msg1> <len2> <msg2> ...}
     *
     * @param messages the list of messages to send
     */
    @Override
    public void sendHistory(LinkedList<String> messages) {
        socketOut.print("HISTORY " + messages.size());
        for (String message : messages)
            socketOut.printf(" %d %s", message.length(), message);
        socketOut.println();
    }

    /**
     * Sends a public message to the client.
     *
     * Format: {@code MSG <date> <message>}
     *
     * @param date the date on which the message was received
     * @param message the contents of the message
     */
    @Override
    public void sendMessage(String date, String message) {
        socketOut.println("MSG " + date + " " + message);
    }

    /**
     * Sends a private message to the client from another user.
     *
     * Format: {@code PRIVATE <date> <username> <message>}
     *
     * @param date the date on which the message was received
     * @param username the source of the message
     * @param message the contents of the message
     */
    @Override
    public void sendPrivateMessage(String date, String username, String message)
    {
        socketOut.println("PRIVATE " + date + " " + username + " " + message);
    }

    /**
     * Sends a list of all users currently logged in to the server.
     *
     * Format: {@code USERS <user1> <user2> <user3> ...}
     *
     * @param users the list of users currently on the server
     */
    @Override
    public void sendUserList(String[] users) {
        socketOut.println("USERS " + String.join(" ", users));
    }

    /**
     * Handles a line of input from the client.
     *
     * Socket clients and servers communicate using text-based,
     * newline-terminated commands. Arguments are space-separated; the first
     * element indicates which command it is.
     *
     * @param input a command to process from the client
     */
    private void handleInput(String input) {
        String[] command = input.split(" ", 2);
        String[] subCommand;
        isActive = true;
        System.out.println("CLIENT: " + input);
        try {
            switch (command[0]) {
                // CONNECT: a new connection request from a socket client
                // Format: CONNECT <username>
                case "CONNECT":
                    changeUsername(command[1]);
                    sessionId = server.addUser(this);
                    break;

                // PING: a ping request from a client
                // Format: PING
                case "PING":
                    socketOut.println("PONG");
                    break;

                // MSG: a public message sent by the client
                // Format: MSG <message>
                case "MSG":
                    server.addMessage(sessionId, command[1]);
                    break;

                // PRIVATE: a private message sent by the client to another user
                // Format: PRIVATE <username> <message>
                case "PRIVATE":
                    subCommand = command[1].split(" ", 2);
                    try {
                        server.addPrivateMessage(
                                sessionId, subCommand[0], subCommand[1]
                        );
                    } catch (UserNotFoundException e) {
                        sendError(e.getCode(), command[1]);
                    }
                    break;

                // RENAME: changes the current client's username
                // Format: RENAME <username>
                case "RENAME":
                    server.renameUser(sessionId, command[1]);
                    break;

                // DISCONNECT: disconnects the current client from the server
                // Format: DISCONNECT
                case "DISCONNECT":
                    disconnect();
                    break;

                // Unknown command
                default:
                    System.err.println("ERROR: Invalid command");
            }
        } catch (ServerException e) {
            sendError(e.getCode());
        }
    }

    /**
     * Sends an error code to the client, with optional arguments.
     *
     * Format: {@code ERROR <code> <arguments>...}
     *
     * @param errorCode the error's code number
     * @param arguments optional arguments, for certain errors
     */
    private void sendError(int errorCode, String... arguments) {
        if (arguments.length > 0)
            socketOut.printf(
                    "ERROR %d %s", errorCode, String.join(" ", arguments));
        else
            socketOut.print("ERROR " + errorCode);
        socketOut.println();
    }

    /**
     * Disconnects the current client from the server and stops listening.
     *
     * Format: {@code DISCONNECT}
     *
     * @throws ServerException if the client couldn't be disconnected cleanly
     */
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
