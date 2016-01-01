package marno.server;

import marno.protocol.MarnoProtocol;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * The socket implementation of the Marno server.
 */
class SocketServer extends Server {

    /**
     * The socket to listen on for incoming client connections.
     */
    private final ServerSocket listenSocket;

    /**
     * The pool of client threads.
     */
    private final ExecutorService pool;

    /**
     * Constructs a new server, ready to be run.
     *
     * @param serverPort the port to listen on
     * @param historyFilename the filename of the history file
     * @throws IOException if the history file could not be opened
     */
    public SocketServer(int serverPort, String historyFilename)
            throws IOException {
        super(serverPort, historyFilename);
        listenSocket = new ServerSocket(port);
        pool = Executors.newCachedThreadPool();
    }

    /**
     * Makes the server run forever.
     *
     * Waits for a new client connection, then creates a new session for it in
     * its own thread.
     */
    @Override
    public void run() {
        System.out.println("Socket Server listening on port " + port);
        for (;;) {
            try {
                Socket clientSocket = listenSocket.accept();
                clientSocket.setSoTimeout(MarnoProtocol.TIMEOUT);
                SocketSession session = new SocketSession(this, clientSocket);
                pool.execute(session);
            } catch (IOException e) {
                System.err.println("ERROR: Failed to create new session");
            }
        }
    }
}
