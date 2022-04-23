import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class grid {
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
                            grid[x][y] = new cell(true);
                        }

                        else if( curChar == '.' )
                        {
                            grid[x][y] = new cell(false);
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
                int numNeighbors = this.findNeighbors( x, y, oldGrid );

                /*if( x == 9 && y == 9 )
                {
                    System.out.println("Num of neighbors at 9,9 " + numNeighbors);
                }*/

                if( oldGrid[x][y].isAlive == true )
                {
                    System.out.println("Current coords " + x + " " + y );
                    System.out.println("Num of neighbors " + numNeighbors);
                }

                // if the cell has less than two neighbors 
                // kill the cell
                if ( numNeighbors < 2 && oldGrid[x][y].isAlive == true )
                {
                    this.killCell(x, y);
                }

                // If the cell has 2 or 3
                // neighbors it moves onto the next 
                // generation
                else if ( ( numNeighbors == 2 || numNeighbors == 3 ) && 
                            oldGrid[x][y].isAlive == true )
                {
                    continue;
                }

                // If the cell has more than 3 
                // neighbors kill the cell 
                else if ( numNeighbors > 3 && oldGrid[x][y].isAlive == true )
                {
                    this.killCell(x, y);
                }

                // If the cell is dead
                // and has three neighbors then 
                // it lives
                else if ( numNeighbors == 3 && oldGrid[x][y].isAlive == false )
                {
                    this.reproduceCell(x, y);
                }
            }
        }
    }

    private int findNeighbors ( int x, int y, cell[][] oldGrid )
    {
        int numNeighbors = 0;
        // Check the position back one, and up one
        if ( x > 0 && y > 0 )
        {
            if( oldGrid[x - 1][y - 1].isAlive == true )
            {
                numNeighbors++;
            }
        }
        // Check the position back one 
        if ( x > 0 )
        {
            if ( oldGrid[x - 1][y].isAlive == true)
            {
                numNeighbors++;
            }
        }

        // Check the position back one, and below one 
        if( x > 0 && y < gridHeight - 2 )
        {
            if( oldGrid[x - 1][y + 1].isAlive == true )
            {
                numNeighbors++;
            }
        }

        // Check the postion above one 
        if ( y > 0 )
        {
            if ( oldGrid[x][y - 1].isAlive == true )
            {
                numNeighbors++;
            }
        }

        // Check the position below one 
        if ( y < gridHeight - 2 )
        {
            if ( oldGrid[x][y + 1].isAlive == true )
            {
                numNeighbors++;
            } 
        }

        // Check the next position, and above one 
        if ( x < gridWidth - 2 && y > 0)
        {
            if ( oldGrid[x + 1][y - 1].isAlive == true )
            {
                numNeighbors++;
            }
        }

        // Check the enxt position 
        if( x < gridWidth - 2 )
        {
            if ( oldGrid[x + 1][y].isAlive == true )
            {
                numNeighbors++;
            }
        }

        // Check the next position, below one
        if ( x < gridWidth - 2 && y < gridHeight - 2 )
        {
            if ( oldGrid[x + 1][y + 1].isAlive == true )
            {
                numNeighbors++;
            }
        }

        return numNeighbors;
    }

    public cell[][] copyGrid ()
    {
        cell copiedGrid[][] = new cell[gridWidth][gridHeight];
        // Go through each element in the grid, and create a new element
        for ( int x = 0; x < gridWidth; x++ )
        {
            for ( int y = 0; y < gridHeight; y++ )
            {
                    copiedGrid[x][y] = new cell(grid[x][y].isAlive);
            }
        }

        return copiedGrid;

    }

    private void reproduceCell ( int x, int y) { this.grid[x][y].isAlive = true; }

    private void killCell ( int x, int y) { this.grid[x][y].isAlive = false; }
}
