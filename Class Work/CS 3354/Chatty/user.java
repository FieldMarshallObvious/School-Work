package Chatty;

public class user {
    private String username = null;
    private int index;
    //private window userWindow;
    
    public user( String u , int i)
    {
        username = u;
        index = i;
    }
    public String getUsername() {return username;}
    public void setUsername( String in ) {username = in;}

    public int getIndex() {return index;}    
}
