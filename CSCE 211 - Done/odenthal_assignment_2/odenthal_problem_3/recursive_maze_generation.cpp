// Entire code authored by Quinton Odenthal
// Recursively creates solvable maze

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 40;

void fillMaze(char maze[][WIDTH], int TLCx, int TLCy, int BRCx, int BRCy);
void printMaze(char maze[][WIDTH]);

void fillMaze(char maze[][WIDTH], int TLCx, int TLCy, int BRCx, int BRCy)
{
	int width = BRCx - TLCx + 1;
	int height = BRCy - TLCy + 1;

	if ((width <= 2) || (height <= 2))
	{
		return;
	}
	else
	{
		if (height >= width)
		{
			int row;
			row = rand() % (height - 2) + 1 + TLCy; // Random row excluding the top and bottom

			for (int i=0; i<width; ++i)
			{
				maze[row][i + TLCx] = 'X'; // Fills row with walls
			}

			if (maze[row][TLCx + width] == ' ') // If the area after the right end of the wall is a space
			{
				maze[row][TLCx + width - 1] = ' '; // Make the right end of the wall a space
			}
			if (maze[row][TLCx - 1] == ' ') // If the area after the left end of the wall is a space
			{
				maze[row][TLCx] = ' '; // Make the left end of the wall a space
			}

			int hole;
			hole  = (rand() % width) + TLCx; // Random segment along the new wall
			maze[row][hole] = ' '; // Creates an oppening

			fillMaze(maze, TLCx, TLCy, BRCx, row - 1); // Recursively call fillMaze on the empty area above the wall

			fillMaze(maze, TLCx, row + 1, BRCx, BRCy); // Recursively call fillMaze on the empty area below the new wall
		}
		else // The width is greater than the height
		{
			int column;
                        column = rand() % (width - 2) + 1 + TLCx; // Random column excluding the left and right

                        for (int i=0; i<height; ++i)
                        {
                                maze[i + TLCy][column] = 'X'; // Fills column with walls
                        }

                        if (maze[TLCy + height][column] == ' ') // If the area under the bottom end of the wall is a space
                        {
                                maze[TLCy + height - 1][column] = ' '; // Make the bottom end of the wall a space
                        }
                        if (maze[TLCy - 1][column] == ' ') // If the area above the top end of the wall is a space
                        {
                                maze[TLCy][column] = ' '; // Make the top end of the wall a space
                        }

                        int hole;
                        hole = (rand() % height) + TLCy; // Random segment along the new wall
			maze[hole][column] = ' '; // Creates an oppening

                        fillMaze(maze, column + 1, TLCy, BRCx, BRCy); // Recursively call fillMaze on the empty area to the right of the new wall

                        fillMaze(maze, TLCx, TLCy, column - 1, BRCy); // Recursively call fillMaze on the empty area to the left of the new wall
		}
	}
}

void printMaze(char maze[][WIDTH])
{
        for (int y = 0; y < HEIGHT; y++)
        {
                for (int x = 0; x < WIDTH; x++)
                {
                                cout << maze[y][x];
                }
                cout << endl;
        }
}

int main()
{
	srand(time(NULL));

	char maze[HEIGHT][WIDTH];

	for (int i=0; i<HEIGHT; i++)
        {
                if (i == 0 || i == (HEIGHT - 1) ) // Top and bottom rows
                {
                        for (int j=0; j<WIDTH; j++) // Fills entire row with Xs
                        {
                                maze[i][j] = 'X';
                        }
                }
		else
		{
			for (int j=0; j<WIDTH; j++)
			{
				if (j == 0 || j == WIDTH - 1)
				{
					maze[i][j] = 'X'; // Fills left and right columns with walls
				}
				else
				{
					maze[i][j] = ' '; // Fills area inside walls with space
				}
			}
		}
	}

	fillMaze(maze, 1, 1, WIDTH - 2, HEIGHT - 2);
	printMaze(maze);

	return 0;
}

