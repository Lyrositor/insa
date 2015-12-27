package client;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;
import static protocol.MarnoProtocol.ERROR_MESSAGES;

public class SocketClient extends Client implements Runnable {

    private Socket socketServer = null;
    private PrintStream socketOut = null;
    private BufferedReader socketIn = null;
    
    private Thread thread = null;
    private boolean continuate = true;

    @Override
    void Connect(String host, String port) throws Exception {
        socketServer = new Socket(host, Integer.parseInt(port));

        socketIn = new BufferedReader(new InputStreamReader(socketServer.getInputStream()));
        socketOut = new PrintStream(socketServer.getOutputStream());

        socketOut.println("CONNECT " + username);

        thread = new Thread(this);
        thread.start();
    }

    @Override
    void Disconnect() throws Exception {
        socketOut.println("DISCONNECT\n");
        
        continuate = false;
        
        socketOut.close();
        socketIn.close();
        socketServer.close();
    }

    @Override
    void SendToServer(String message) throws Exception {
        socketOut.println("MSG " + message);
    }

    @Override
    public void run() {
        String line;
        continuate = true;
        try {
            // !Thread.currentThread().isInterrupted() &&
            while (continuate != false && (line = socketIn.readLine()) != null) {
                handleMessage(line);
            }
        } catch (Exception e) {
            System.err.println("[Client exception]: " + e.getMessage());
        }
    }

    private void handleMessage(String line) {
        String[] elements = line.split(" ", 2);
        String[] subElements;
        
        switch (elements[0]) {
            case "HISTORY":
                // Handle history
                // Format : HISTORY <num> <len1> <msg1> <len2> <msg2> ...
                subElements = elements[1].split(" ");
                int countMessage = 0;
                int nbrMessage = 0;
                while (nbrMessage < Integer.parseInt(subElements[0])) {
                    String message = "";
                    int count = countMessage + 2;
                    while (message.length() <= Integer.parseInt(subElements[countMessage + 1])) {
                        message += subElements[count++] + " ";
                    }
                    window.addChatText(message);
                    nbrMessage++;
                    countMessage = count - 1;
                }
                break;

            case "MSG":
                // Handle normal message
                window.addChatText(elements[1]);
                break;

            case "PRIVATE":
                // Handle private message
                subElements = elements[1].split(" ");
                window.addChatText("*" + subElements[1] + "* " + subElements[2]);
                break;

            case "USERS":
                // Handle user list
                String[] users = elements[1].split(" ");
                DefaultListModel listModel = new DefaultListModel();
                for(String user : users) {
                    listModel.addElement(user);
                }
                window.listUser.setModel(listModel);
                break;
                
            case "ERROR":
                // Handle error
                int errorNumber = Integer.parseInt(elements[1]);
                JOptionPane.showMessageDialog(null, ERROR_MESSAGES[errorNumber], "Error", 0);
                
                if(errorNumber == 1) { // Invalid username => disconnect
                    window.disconnect();
                }
                break;

            default:
                System.err.println("Unrecognized: " + line);
                break;
        }
    }

}
