package marno.client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import javax.swing.DefaultListModel;
import marno.protocol.RMIClientInterface;
import marno.protocol.RMIConfig;
import marno.protocol.RMIServerInterface;

/**
 * Implementation of the Client class for RMI connection, with the RMI Client Interface
 */
public class RMIClient extends Client implements RMIClientInterface {

    /**
     * The unique number of the client session
     */
    private String sessionId;
    /**
     * Link to the RMI server
     */
    private RMIServerInterface stub;

    /**
     * Constructor with the main GUI window, and create a reference object of this client
     * @param window the main GUI window
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
     * Launch a connection with the server, at the host with the port number.
     * Launch two threads too, one to receive informations, and another to ping-pong
     * @param host the hostname of the server
     * @param port the port number of the server
     * @throws Exception raise an exception if connection fail
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
        }
    }
    
    /**
     * Close the connection with the server
     * @throws Exception raise an exception if a problem appear
     */
    @Override
    public void disconnect() throws Exception {
        stub.disconnect(this.sessionId);
    }

    /**
     * Send a message to all people of the server with the output stream
     * @param message the message to sent
     * @throws RemoteException raise an exception if a problem appear
     */
    @Override
    public void sendMessageToServer(String message) throws RemoteException {
        stub.sendMessage(this.sessionId, message);
    }

    /**
     * Send a private message to an user at the server
     * @param username the user who receive the message
     * @param message the message to sent
     * @throws Exception raise an exception if a problem appear
     */
    @Override
    void sendPrivateMessageToServer(String username, String message)
            throws Exception {
        stub.sendPrivateMessage(this.sessionId, username, message);
    }

    /**
     * Receive a message from the server and add to the chat
     * @param date date of emission of the message
     * @param message the content text
     * @throws RemoteException raise an exception if a problem appear
     */
    @Override
    public void sendMessage(String date, String message)
            throws RemoteException {
        window.addChatText(date + " " + message);
    }

    /**
     * Receive the history of message (one by one) from the server and add to the chat
     * @param history
     * @throws RemoteException raise an exception if a problem appear
     */
    @Override
    public void sendHistory(LinkedList<String> history)
            throws RemoteException {
        window.addChatText(String.join("\n", history), false);
    }

    /**
     * Receive a private message, and add it to the chat
     * @param date date of emission of the message
     * @param username the user who send the private message
     * @param message the content text of the private message
     * @throws RemoteException raise an exception if a problem appear
     */
    @Override
    public void sendPrivateMessage(String date, String username, String message)
            throws RemoteException {
        window.addChatText(date + " {" + username + "} " + message);
    }

    /**
     * Receive the user list of people actually connected to the server
     * @param users
     * @throws RemoteException raise an exception if a problem appear
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
     * Ping
     * @throws RemoteException raise an exception if a problem appear
     */
    @Override
    public void ping() throws RemoteException {
    }

}
