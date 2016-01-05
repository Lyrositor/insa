package marno.client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;
import static marno.protocol.MarnoProtocol.ERROR_MESSAGES;
import marno.protocol.RMIClientInterface;
import marno.protocol.RMIConfig;
import marno.protocol.RMIServerInterface;

/**
 * The RMI implementation of the Marno client.
 */
public class RMIClient extends Client implements RMIClientInterface {

    /**
     * The unique ID of the client session.
     */
    private String sessionId;

    /**
     * The RMI server currently connected to.
     */
    private RMIServerInterface stub;

    /**
     * Ties the client to its GUI window, then exports this client as a remote
     * RMI object, ready for the server to use.
     *
     * @param window the client's main GUI window
     */
    public RMIClient(ClientGUI window) {
        super(window);

        try {
            RMIClientInterface ref = (RMIClientInterface) UnicastRemoteObject.exportObject(this, 0);
        } catch (Exception e) {
            System.err.println("[Client exception]: " + e.getMessage());
        }
    }

    /**
     * Initiates a connection with the specified server.
     *
     * @param host the hostname of the server
     * @param port the port number of the server
     * @throws Exception if the connection fails
     */
    @Override
    public void connect(String host, String port) throws Exception {
        Registry registry = LocateRegistry.getRegistry(
                host, Integer.parseInt(port)
        );
        stub = (RMIServerInterface) registry.lookup(RMIConfig.REGISTRY_NAME);
        window.textAreaChat.setText("");

        try {
            sessionId = stub.connect(username, this);
        } catch (RemoteException e) {
            // Handle invalid username
            JOptionPane.showMessageDialog(
                    null, ERROR_MESSAGES[1], "Error",
                    JOptionPane.ERROR_MESSAGE
            );
            this.disconnect();
            window.disconnect();
        }
    }

    /**
     * Closes the connection with the server.
     *
     * @throws Exception if the client is unable to cleanly disconnect
     */
    @Override
    public void disconnect() throws Exception {
        stub.disconnect(this.sessionId);
    }

    /**
     * Sends a public message to the server.
     *
     * @param message the contents of the message
     * @throws RemoteException if an error occurs
     */
    @Override
    public void sendMessageToServer(String message) throws RemoteException {
        stub.sendMessage(this.sessionId, message);
    }

    /**
     * Sends a private message to another client connected to the server.
     *
     * @param username the username of the intended recipient
     * @param message the contents of the message
     * @throws Exception if an error occurs
     */
    @Override
    void sendPrivateMessageToServer(String username, String message)
            throws Exception {
        stub.sendPrivateMessage(this.sessionId, username, message);
    }

    /**
     * Receives a message from the server and adds it to the chat box.
     *
     * @param date date of emission of the message
     * @param message the message's contents
     * @throws RemoteException if an error occurs
     */
    @Override
    public void sendMessage(String date, String message)
            throws RemoteException {
        window.addChatText(date + " " + message);
    }

    /**
     * Receives all previous messages received by the server and adds them to
     * the chat box.
     *
     * @param history a list of messages in the history
     * @throws RemoteException if an error occurs
     */
    @Override
    public void sendHistory(LinkedList<String> history)
            throws RemoteException {
        window.addChatText(String.join("\n", history), false);
    }

    /**
     * Receives a private message, and adds it to the chat (with special
     * formatting).
     *
     * @param date date of emission of the message
     * @param username the sender of the message
     * @param message the contents of the message
     * @throws RemoteException if an error occurs
     */
    @Override
    public void sendPrivateMessage(String date, String username, String message)
            throws RemoteException {
        window.addChatText(date + " {" + username + "} " + message);
    }

    /**
     * Receives the list of clients currently connected to the server.
     * @param users the list of users connected to the server
     * @throws RemoteException if an error occurs
     */
    @Override
    public void sendUserList(String[] users) throws RemoteException {
        DefaultListModel listModel = new DefaultListModel();
        for (String user : users) {
            listModel.addElement(user);
        }
        window.listUser.setModel(listModel);
    }

    /**
     * Receives a ping from the server.
     *
     * Used by the server to check that the client is still alive. If the client
     * has become unreachable, an exception will be raised on the server-side.
     *
     * @throws RemoteException if the client cannot be reached
     */
    @Override
    public void ping() throws RemoteException {
    }

}
