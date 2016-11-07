#include <stdio.h>
#include <stdlib.h>
#define LEFTDIAG 1
#define RIGHTDIAG 1
#define BOX FALSE

//This allows for the array size to be changed easily w/o
//extensive code modification
#define BOARDSIZE 4

void findAsterisks(char** board);

int main()
{
	//create an array of char pointers
	char* array[BOARDSIZE];
	//create m and n as counters
	int m,n;
	for(m=0;m<BOARDSIZE;m++) // iterate over the y axis
	{
		// allocate memory at each of the pointer so that there is an array of 4 chars
		// for each pointer
		array[m] = (char*)malloc( sizeof( char) );
		for(n=0;n<BOARDSIZE;n++) // iterate over the x axis
		{
			// allocate memory for the array
			// assign the value at that position
			if(LEFTDIAG)
				array[m][n] = '_';
			// if the m and n are equal, set as a * (diagonal from top left)
			if(m==n) array[m][n] = '*';
			// diagonal from top right
			if(m+n == BOARDSIZE - 1) array[m][n] = '*';
			// print all the chars in the array
			printf("%c",array[m][n]);
		}
		// newline after each row
		printf("\n");
	}

	findAsterisks(array);

	return 0;
}

void findAsterisks(char** board)
{
	// error checking, make sure we pass a non-NULL board to the function
	if(board == NULL)
		return;
	else
	{
		int m,n; // create our counter variables
		for(m=0;m<BOARDSIZE;m++)
		{ // iterate over the x coords
			for(n=0;n<BOARDSIZE;n++)
			{ // iterate over the y coord
				if(board[m][n] == '*')
				{ // if the point is set to an asterisk, declare so.
					printf("Asterisk at: (%d, %d)\n",m,n);
				}
			}
		}
	}
}
