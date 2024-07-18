// Entire code authored by Quinton Odenthal
// Creates a truely random, and sometimes unsolvable, maze and tries to solve it

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

// Function prototypes
void printMaze(char maze[][WIDTH], int curx, int cury);
bool validMove(char maze[][WIDTH], bool visited[][WIDTH],int newX, int newY);
bool search(char maze[][WIDTH], bool visited[][WIDTH], int x, int y, int& i, int pathXCoords[], int pathYCoords[]);
void fillMaze(char maze[][WIDTH]);
void assignStart(char maze[][WIDTH], int& x, int& y);
void assignExit(char maze[][WIDTH]);


// Return true or false if moving to the specified coordinate is valid
// Return false if we have been to this cell already
bool validMove(char maze[][WIDTH], bool visited[][WIDTH],
	int newX, int newY)
{
	// Check for going off the maze edges
	if (newX < 0 || newX >= WIDTH)
		return false;
	if (newY < 0 || newY >= HEIGHT)
		return false;
	// Check if target is a wall
	if (maze[newY][newX] == 'X')
		return false;
	// Check if visited
	if (visited[newY][newX])
		return false;
	return true;
}


// Display the maze in ASCII
void printMaze(char maze[][WIDTH], int curx, int cury)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if ((x == curx) && (y == cury))
				cout << "@";
			else
				cout << maze[y][x];
		}
		cout << endl;
	}
}

// Recursively search from x,y until we find the exit
bool search(char maze[][WIDTH], bool visited[][WIDTH], int x, int y, int& i, int pathXCoords[], int pathYCoords[])
{
	i++; // Number of coordinates to store
	int moveNum = i; // The move number for each call
	cout << moveNum << endl; // DEBUGGING
	if (maze[y][x] == 'E')
		pathXCoords = new int[i];
		pathYCoords = new int[i];
		return true;

	bool foundExit = false;
	visited[y][x] = true;
	if (validMove(maze, visited, x, y - 1))
		foundExit = search(maze, visited, x, y - 1, i, pathXCoords, pathYCoords);
	if (!foundExit && (validMove(maze, visited, x, y + 1)))
		foundExit = search(maze, visited, x, y + 1, i, pathXCoords, pathYCoords);
	if (!foundExit && (validMove(maze, visited, x - 1, y)))
		foundExit = search(maze, visited, x - 1, y, i, pathXCoords, pathYCoords);
	if (!foundExit && (validMove(maze, visited, x + 1, y)))
		foundExit = search(maze, visited, x + 1, y, i, pathXCoords, pathYCoords);

	if (foundExit)
	{
		pathXCoords[moveNum-1] = x; // Storing the coordinates of the user's position for every move,
		pathYCoords[moveNum-1] = y; // in the correct order
		return true;
	}
	return false;
}

// Fills the 2-dimentional array with walls and paths
void fillMaze(char maze[][WIDTH])
{
	for (int i=0; i<HEIGHT; i++)
	{
		if (i == 0 || i == (HEIGHT - 1) ) // Top and bottom rows
		{
			for (int j=0; j<WIDTH; j++) // Fills entire row with Xs
			{
				maze[i][j] = 'X';
			}
		}
		else // All rows between top and bottom
		{
			for (int j=0; j<WIDTH; j++)
			{
				if (j == 0 || j == (WIDTH - 1) ) // Left and Right columns
				{
					maze[i][j] = 'X'; // Fills entire column with Xs
				}
				else // All columns between left and right
				{
					if ( (rand() % 4) == 0) // 25% of the time makes a wall
					{
						maze[i][j] = 'X';
					}
					else  // 75% of the time makes a path
					{
						maze[i][j] = ' ';
					}
				}
			}
		}
	}
}

// Assigns start point
void assignStart(char maze[][WIDTH], int& x, int& y)
{
	x = 1 + (rand() % (WIDTH - 3) ); // Random location inside the outer walls of the maze
	y = 1 + (rand() % (HEIGHT - 3) );

	if (maze[y][x] != ' ') // If random location isn't a path, tries again
	{
		assignStart(maze, x, y);
	}
}

// Assigns exit point
void assignExit(char maze[][WIDTH])
{
        int x = 1 + (rand() % (WIDTH - 3) ); // Random location inside the outer walls of the maze
        int y = 1 + (rand() % (HEIGHT - 3) );

        if (maze[y][x] == ' ') // If random location is a path, creates exit
        {
                maze[y][x] = 'E';
        }
	else // If random location isn't a path, tries again
	{
		assignExit(maze);
	}
}


int main()
{
	char maze[HEIGHT][WIDTH];
	bool visited[HEIGHT][WIDTH];

	int x, y;
	int numMovesTotal = 0;
	bool foundExit = false;

	int* pathXCoords = NULL;
	int* pathYCoords = NULL;

	srand(time(NULL));

	// Initialize visited locations to false
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
			visited[y][x] = false;
	}
	visited[y][x] = true;

	fillMaze(maze);
	assignExit(maze);
	assignStart(maze, x, y);
	printMaze(maze, x, y);
	search(maze, visited, x, y, numMovesTotal, pathXCoords, pathYCoords);

	cout << numMovesTotal << endl; // Debugging

	for (int i=0; i<numMovesTotal; i++)
	{
		printMaze(maze, pathXCoords[i], pathYCoords[i]);
	}
	return 0;
}
