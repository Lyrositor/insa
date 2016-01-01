package client;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.LinkedList;
import javax.swing.DefaultListModel;
import protocol.RMIClientInterface;
import protocol.RMIConfig;
import protocol.RMIServerInterface;

public class RMIClient extends Client implements RMIClientInterface {

    private String sessionId;
    private RMIServerInterface stub;

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

    @Override
    public void disconnect() throws Exception {
        stub.disconnect(this.sessionId);
    }

    @Override
    public void sendMessageToServer(String message) throws RemoteException {
        stub.send(this.sessionId, message);
    }

    @Override
    void sendPrivateMessageToServer(String username, String message)
            throws Exception {
        stub.sendPrivateMessage(this.sessionId, username, message);
    }

    @Override
    public void sendMessage(String date, String message)
            throws RemoteException {
       window.addChatText(date + " " + message);
    }

    public void sendHistory(LinkedList<String> history)
            throws RemoteException {
        window.addChatText(String.join("\n", history), false);
    }

    @Override
    public void sendPrivateMessage(String date, String username, String message)
            throws RemoteException {
        window.addChatText(date + " {" + username + "} " + message);
    }

    @Override
    public void sendUserList(String[] users) throws RemoteException {
        DefaultListModel listModel = new DefaultListModel();
        for(String user : users) {
            listModel.addElement(user);
        }
        window.listUser.setModel(listModel);
    }

    @Override
    public void ping() throws RemoteException {
    }

}
