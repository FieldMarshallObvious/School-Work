import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class gameRunner {
    public static void main ( String args[] )
    {
        // Create a grid
        grid gameGrid = new grid(20, 20, "gameState.txt");

        // Should the program continue
        boolean continueProgram = true;
        // User input 
        String userInput = "";
        // num of computations
        int numOfComputations = 0;

        // Read through the file, to 
        Scanner inputFile;

        try {
            inputFile = new Scanner(new File("gameState.txt"));

            // Gather the number for computation needed
            while ( inputFile.hasNextLine() )
            {
                String newLine = inputFile.nextLine();

                // If we are at the end of 
                // file log the number of computation
                if ( !(inputFile.hasNextLine()) )
                {
                    numOfComputations = Integer.parseInt(newLine); 
                }
            }
        } catch ( FileNotFoundException error ) {
            System.out.print("Error opening file");
            error.printStackTrace();
        }

        // Move the grid the number of
        // times required in input
        for ( int x = 0; x < numOfComputations; x++ )
        {
            gameGrid.nextMove();    
        }

        // Display the final state of the grid
        gameGrid.displayGrid();
    }
}
