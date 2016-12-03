#include <stdio.h>
#include <string.h>
#include <mover.c>

void mark_adjacency(char adj[4][2])
{	
	for (int i = 0; i < 4; i++)
	{
		char k = strlen(poss[ adj[i][0] ][ adj[i][1] ]);
		int m = adj[i][0]; // the x of the adjacent block
		int n = adj[i][1]; // the y of the adjacent block

		if (m > 3 || m < 0 || n > 3 || n < 0)
			continue;
		else
			if (signal == 0)
				real[m][n] = 9;

			else if (signal == 1)
				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 1)
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 1;

			else if (siganl == 2)
				if (real[m][n] == 0) // if no real value
					int p = 0;
					for (int i=0; i<k; i++) 
					// if find 2 in possible values
					// set the real value to 2
					{
						if (poss[m][n][i] == 2)
							real[m][n] = 2;
							p = p++;
							break;
					}
					// if no 2 in possible values
					// put 2 in possible value
					if (p == 0)
						poss[m][n][k] = 2;

			else if (signal == 3)
				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 2)
							real[m][n] = 2;
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 2;

				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 1)
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 1;

			else if (signal == 4)
				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 4)
							real[m][n] = 4;
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 4;

			else if (signal == 5)
				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 4)
							real[m][n] = 4;
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 4;


				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 1)
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 1;

			else if (siganl == 6)
				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 4)
							real[m][n] = 4;
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 4;

					if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 2)
							real[m][n] = 2;
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 2;

			else if (signal == 7)
				if (real[m][n] == 0)
				int p = 0;
				for (int i=0; i<k; i++)
				{
					if (poss[m][n][i] == 4)
						real[m][n] = 4;
						p = p++;
						break;
				}
				if (p == 0)
					poss[m][n][k] = 4;

				if (real[m][n] == 0)
				int p = 0;
				for (int i=0; i<k; i++)
				{
					if (poss[m][n][i] == 2)
						real[m][n] = 2;
						p = p++;
						break;
				}
				if (p == 0)
					poss[m][n][k] = 2;		

				if (real[m][n] == 0)
					int p = 0;
					for (int i=0; i<k; i++)
					{
						if (poss[m][n][i] == 1)
							p = p++;
							break;
					}
					if (p == 0)
						poss[m][n][k] = 1;
	}
}

int face_edge(x,y)
{
	
}

int main ()
{
	int x = 0, y = 0;
	int input = 8;
	int adj[4][2] = {{x+1,y},{x-1,y},{x,y+1},{x,y-1}};
	int real[4][4];
	int poss[4][4][4]; 

	while (signal != 8)
	{
		scanf("%d",&signal);
		mark_adjacency();

		switch (input)
		{
			case 0:
				move();
				break;
			case 1:
				turn_and_move();
				break;
			case 2||3:
				for (int i = 0; i < 4; i++)  // 0 is forward , 1 is right, 2 is back, 3 is left
				{
					if (real[adj[i][0]][adj[i][0]] == 2)
						// kill
						move_to_that();
						break;
					else
						turn_and_move(); // back, turn right, go forward
						break;
				}
			case 4||5||6||7:
				for (int i = 0; i < 4; i++)
				{
					if (real[adj[i][0]][adj[i][0]] == 4)
						move_to_that();
						break;
					else if (real[adj[i][0]][adj[i][0]] == 2)
						// kill
						move_to_that();
										
						break;
					else
						turn_and_move();
						break;
				}



		}
	}


}	
