public class cell {
    public boolean isAlive;
    public int x;
    public int y;

    public cell( )
    {
        isAlive = false;
        x = 0;
        y = 0;
    }

    public cell ( boolean aliveCondition, int newX, int newY )
    {
        isAlive = aliveCondition;
        x = newX;
        y = newY;
    }

    public void deterimineState ( cell[][] oldGrid, int gridHeight, int gridWidth )
    {
        int numNeighbors = this.findNeighbors( x, y, oldGrid, gridHeight, gridWidth );

        // if the cell has less than two neighbors 
        // kill the cell
        if ( numNeighbors < 2 && oldGrid[x][y].isAlive == true )
        {
            this.killCell();
        }

        // If the cell has 2 or 3
        // neighbors it moves onto the next 
        // generation
        else if ( ( numNeighbors == 2 || numNeighbors == 3 ) && 
                    oldGrid[x][y].isAlive == true )
        {
            return;
        }

        // If the cell has more than 3 
        // neighbors kill the cell 
        else if ( numNeighbors > 3 && oldGrid[x][y].isAlive == true )
        {
            this.killCell();
        }

        // If the cell is dead
        // and has three neighbors then 
        // it lives
        else if ( numNeighbors == 3 && oldGrid[x][y].isAlive == false )
        {
            this.reproduceCell();
        }
    }

    private int findNeighbors ( int x, int y, cell[][] oldGrid, int gridHeight, int gridWidth )
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

    private void reproduceCell () { this.isAlive = true; }

    private void killCell ( ) { this.isAlive = false; }
}