import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.*;

public class grid  {
    public cell grid[][];
    private int gridWidth;
    private int gridHeight;

    public grid( int width, int height )
    {
        gridWidth = width;
        gridHeight = height;

        grid = new cell[width][height]; 

        // Initialize each item of grid
        // with a new 
        for ( int x = 0; x < width; x++ )
        {
            for ( int y = 0; y < height; y++ )
            {
                grid[x][y] = new cell();
            }
        }
    }

    public grid ( int width, int height, String file )
    {
        gridWidth = width;
        gridHeight = height;

        grid = new cell[width][height];

        // Open the input file
       Scanner userInput;
       
       // attempt to open the given file 
       try {
            userInput = new Scanner( ( new File(file) ) );

            // Initalize ach item of the grid
            // to the file input 
            while ( userInput.hasNextLine() )
            {
                for ( int x = 0; x < width; x++ )
                {
                    String curLine = userInput.nextLine();
                    for ( int y = 0; y < height; y++ )
                    {
                        char curChar = curLine.charAt(y);
                        // If the cur char is set to alive
                        if ( curChar == 'X' )
                        {
                            grid[x][y] = new cell(true, x, y);
                        }

                        else if( curChar == '.' )
                        {
                            grid[x][y] = new cell(false, x, y);
                        }
                    }
                }
                // Move over the next line to skip computation 
                // number
                userInput.nextLine();
            }
       } catch (FileNotFoundException error) {
            System.out.print("Error opening file");
            error.printStackTrace();
        }



    }

    public void displayGrid ( )
    {
        for ( int x = 0; x < gridWidth; x++ )
        {
            for ( int y = 0; y < gridHeight; y++ )
            {
                // If the current cell is alive 
                // display an X
                if( grid[x][y].isAlive == true  )
                {
                    System.out.print("X");
                }

                // If the current is not alive 
                // display an .
                else
                {
                    System.out.print(".");
                }
            }
            System.out.println("\n");
        }
    }

    public void nextMove ( )
    {
        // Create a copy of the original grid
        cell oldGrid[][] = this.copyGrid();
        // Check the conditions of each cell in the grid
        // then determine what to do 
        for ( int x = 0; x < gridWidth; x++ )
        {
            for( int y = 0; y < gridHeight; y++ )
            {
                // Create an anyomous thread class 
                // to initialize a thread for each 
                // cell to determine state
                Thread stateThread = new Thread() {
                    cell[][] curGrid;
                    int curX;
                    int curY;
                    int curGridHeight;
                    int curGridWidth;

                    public void run() {
                        grid[curX][curY].deterimineState(curGrid, curGridHeight, curGridWidth);
                    }

                    private Thread init( int newX, int newY, int newGridHeight,
                                         int newGridWidth, cell[][] userGrid )
                    {
                        curX = newX;
                        curY = newY;
                        curGridHeight = newGridHeight;
                        curGridWidth = newGridWidth;
                        curGrid = userGrid;
                        return this;
                    }
                }.init(x, y, gridHeight, gridWidth, oldGrid);

                stateThread.start();
            }
        }
    }

    public cell[][] copyGrid ()
    {
        cell copiedGrid[][] = new cell[gridWidth][gridHeight];
        // Go through each element in the grid, and create a new element
        for ( int x = 0; x < gridWidth; x++ )
        {
            for ( int y = 0; y < gridHeight; y++ )
            {
                    copiedGrid[x][y] = new cell(grid[x][y].isAlive, x, y);
            }
        }

        return copiedGrid;

    }
}
