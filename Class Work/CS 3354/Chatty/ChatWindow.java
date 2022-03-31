package Chatty;

import javax.swing.*;
import java.awt.event.*;
import java.io.BufferedWriter;
import java.io.File;  // Import the File class
import java.io.FileNotFoundException;
import java.io.FileWriter;   // Import the FileWriter class
import java.io.IOException;  // Import the IOException class to handle errors
import java.util.Scanner;
import java.nio.file.*;
import java.awt.*;

public class ChatWindow implements ActionListener{
    
    public String displayName;
    public JTextField input;
    public JTextArea receiving;
    private String message;
    private Scanner chatLog; 


    public ChatWindow(User in) // constructor
    {
        displayName = in.getUsername();
        JFrame jf = new JFrame();

        // Initialize the chat reader 
        try {
            chatLog = new Scanner( ( new File("Chatty/chatLog.txt") ) );
        } catch (FileNotFoundException error) {
            System.out.print("Error opening file");
            error.printStackTrace();
        }
        
        //frame setup
        jf.setSize( 800, 600 ); 
        jf.setTitle("Chatty: " + displayName);
        jf.setContentPane(new JPanel(null));

        // message input setup
        input = new JTextField("Enter a message");
        input.setLocation( 10, 530 );
        input.setSize( 680, 20);
        input.addActionListener( this );

        //message window setup
        receiving = new JTextArea(); 
        receiving.setLocation( 10, 10 );
        receiving.setSize( 760, 510 );
        receiving.setEditable( false );
        JScrollPane scrollPane = new JScrollPane( receiving );

        //scrollbar setup

        JButton send = new JButton("Send"); //send button setup
        send.setLocation( 700 , 530 );
        send.setSize( 70, 20);
        send.addActionListener( this );

        jf.add(input);
        jf.add(receiving);
        jf.add(send);
        jf.setVisible( true );

        jf.setDefaultCloseOperation( JFrame.DISPOSE_ON_CLOSE );

        // Append all existing items
        while( chatLog.hasNextLine() )
        {
            String newMessage = chatLog.nextLine();
            receiving.append( ( newMessage + "\n" ) );
        }
    }

    public void actionPerformed(ActionEvent e)
    {
        message = displayName + ": " + input.getText() + "\n";
        //receiving.append(displayName + ": " + message + "\n");
        try { 
            // Write to the output file 
            FileWriter chatLogWriter = new FileWriter("Chatty/chatLog.txt", true);
            BufferedWriter out = new BufferedWriter(chatLogWriter);
            out.write(message);
            out.close();
        }  catch (IOException err) {
            System.out.println("An error occurred writing to log.");
            err.printStackTrace();
          }
        Chatty.getInstance().publishMessage();
    }

    public void receiveMessage( )
    {
        int curLine = 0;
        int maxLines = 0; 

        // Refresh chat reader 
        try {
            chatLog = new Scanner( ( new File("Chatty/chatLog.txt") ) );
        } catch (FileNotFoundException error) {
            System.out.print("Error opening file");
            error.printStackTrace();
        }

        // Determine the new upadted lines
        while( chatLog.hasNextLine() )
        {
            chatLog.nextLine();
            maxLines++;
        }

        // Refresh chat reader 
        try {
            chatLog = new Scanner( ( new File("Chatty/chatLog.txt") ) );
        } catch (FileNotFoundException error) {
            System.out.print("Error opening file");
            error.printStackTrace();
        }

        // Get new line
        while( chatLog.hasNextLine() )
        {
            String newMessage = chatLog.nextLine();
            if( curLine == (maxLines - 1) )
            {
                receiving.append( ( newMessage + "\n" ) );
            }
            curLine++;
        }
    }

    public String getMessage() { return message;}
}