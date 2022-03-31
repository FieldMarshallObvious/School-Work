package Chatty;

import java.io.File;  
import java.io.IOException;  // Import the IOException class to handle errors



public class Chatty {
    public int numUsers;
    public User[] users;
    public ChatWindow[] windows;
    private static Chatty chattyInstance;
    public static void main(String[] args)
    {
       Chatty curChatInstance = new Chatty();

    }

    public Chatty( ) {
        this.numUsers = 2;
        this.users = new User[numUsers];

        // Create chat log if it hasn't been created already
        File chatLogObj = new File("Chatty/chatLog.txt");
        // If the file does not exist create it 
        try {
            if (chatLogObj.createNewFile()) {
              System.out.println("File created: " + chatLogObj.getName());
            } else {
              System.out.println("File already exists.");
            }
        } catch (IOException err) {
            System.out.println("Error creating file.");
            err.printStackTrace();
        }
        
        for(int i = 0; i < numUsers; i++) 
        {
            users[i] = new User("null" , i);
        }
        
        users[0].setUsername("Tanner");
        users[1].setUsername("Noah"); 
        //can instatiate more users here, granted the amount matches numUsers
        
        this.windows = new ChatWindow[numUsers];

        for(int i = 0; i < numUsers; i++) 
        {
            this.windows[i] = new ChatWindow(users[i]);
        }   

        chattyInstance = this;

    }

    // Return the instance of the chatt
    public static Chatty getInstance() { return chattyInstance; }

    // Send the message to subscribers
    public void publishMessage( )
    {
        for(int i = 0; i < this.numUsers; i++)
        {
            this.windows[i].receiveMessage();
        }
    }
}
