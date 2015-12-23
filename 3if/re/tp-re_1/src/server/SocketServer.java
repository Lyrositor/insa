package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class SocketServer extends Server {

    private static final int MAX_THREADS = 5;

    private final ServerSocket listenSocket;
    private final ExecutorService pool;

    public SocketServer(int serverPort, String historyFilename)
            throws IOException {
        super(serverPort, historyFilename);
        listenSocket = new ServerSocket(port);
        pool = Executors.newFixedThreadPool(MAX_THREADS);
    }

    public void run() {
        System.out.println("Server listening on port " + port);
        for (;;) {
            try {
                Socket clientSocket = listenSocket.accept();
                SocketSession session = new SocketSession(this, clientSocket);
                pool.execute(session);
            } catch (IOException e) {
                System.err.println("ERROR: Failed to create new session");
            }
        }
    }
}
