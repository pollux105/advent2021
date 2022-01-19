/*
--- Day 5: Hydrothermal Venture ---

You come across a field of hydrothermal vents on the ocean floor! 
These vents constantly produce large, opaque clouds, so it would be best to avoid them if possible.

They tend to form in lines; the submarine helpfully produces a list of nearby 
lines of vents (your puzzle input) for you to review. For example:

0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2

Each line of vents is given as a line segment in the format x1,y1 -> x2,y2 
where x1,y1 are the coordinates of one end the line segment and x2,y2 are 
the coordinates of the other end. These line segments include the points at both ends. In other words:

    An entry like 1,1 -> 1,3 covers points 1,1, 1,2, and 1,3.
    An entry like 9,7 -> 7,7 covers points 9,7, 8,7, and 7,7.

For now, only consider horizontal and vertical lines: lines where either x1 = x2 or y1 = y2.

So, the horizontal and vertical lines from the above list would produce the following diagram:

.......1..
..1....1..
..1....1..
.......1..
.112111211
..........
..........
..........
..........
222111....

In this diagram, the top left corner is 0,0 and the bottom right corner is 9,9. 
Each position is shown as the number of lines which cover that point or . if no line covers that point. 
The top-left pair of 1s, for example, comes from 2,2 -> 2,1; 
the very bottom row is formed by the overlapping lines 0,9 -> 5,9 and 0,9 -> 2,9.

To avoid the most dangerous areas, you need to determine the number of points 
where at least two lines overlap. In the above example, this is anywhere in the 
diagram with a 2 or larger - a total of 5 points.

Consider only horizontal and vertical lines. At how many points do at least two lines overlap?

--- Part Two ---

Unfortunately, considering only horizontal and vertical lines doesn't give you the full picture; you need to also consider diagonal lines.

Because of the limits of the hydrothermal vent mapping system, the lines in your list will only ever be horizontal, vertical, or a diagonal line at exactly 45 degrees. In other words:

    An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3.
    An entry like 9,7 -> 7,9 covers points 9,7, 8,8, and 7,9.

Considering all lines from the above example would now produce the following diagram:

1.1....11.
.111...2..
..2.1.111.
...1.2.2..
.112313211
...1.2....
..1...1...
.1.....1..
1.......1.
222111....

You still need to determine the number of points where at least two lines overlap. In the above example, this is still anywhere in the diagram with a 2 or larger - now a total of 12 points.

Consider all of the lines. At how many points do at least two lines overlap?


*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINES 500
#define XMAX 1000
#define YMAX 1000

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define PART1 1
#define PART2 2

int tablines[LINES][4];
int board[XMAX][YMAX];

int main(int argc, char *argv[]){

    int part = 0;
    if ((argv[1] == NULL) || !strcmp(argv[1],"part1"))
	{
		part = PART1;
	}
	else if (!strcmp(argv[1],"part2"))
	{
		part = PART2;
	}
	else
	{
		part = PART1;
	}

    FILE* myfile = fopen("day5.txt","r");
    if (myfile == NULL)
	{
		printf("file not available");
		return 0;
	}

    char * token;
    char delimiter[4] = "-> ,";
    int column = 0;
    int row = 0;
    char dataline[20];
    int sens = 0;
    int x0,y0,x1,y1;

    // init tablines
        for (int i=0; i<LINES; i++)
    {
        for (int j=0; j<4;j++)
        {
            tablines[i][j] = 0;
        }
        
    }
    // fill tablines
    while (fgets(dataline, 50, myfile)!= NULL)
    {
        
        token = strtok(dataline,delimiter);
        tablines[row][column++] = strtol(token,NULL,10);
        while (token != NULL)
        {
            token = strtok(NULL,delimiter);
            tablines[row][column++] = strtol(token,NULL,10);
        }
        column = 0;
        row++;
    }

    // init the board
    for (int i =0; i<XMAX; i++)
        for (int j=0; j<YMAX; j++) board[i][j] = 0;

    // fill the board
    for (int i=0;i<LINES;i++)
    { 
        x0 = tablines[i][0];
        y0 = tablines[i][1];
        x1 = tablines[i][2];
        y1 = tablines[i][3];
        
        if (x0 == x1) 
        {
            for (int j = min(y0,y1); j<=max(y0,y1);j++)
            {
                board[x0][j] = board[x0][j] + 1;
            }
        }
        else if (y0 == y1)
        {
            for (int j = min(x0,x1); j<=max(x0,x1);j++)
            {
                board[j][y0] = board[j][y0] + 1;
            }
        }
        else
        { 
            if (part == PART2) 
            {
                if (x0 < x1 && y0 < y1) sens = 1;
                else if (x0 > x1 && y0 > y1) sens = 2;
                else if (x0 > x1 && y0 < y1) sens = 3;
                else if (x0 < x1 && y0 > y1) sens = 4;
                if (sens == 1)
                {
                    while (x0<=x1)
                    {
                        board[x0++][y0++]+=1;
                    }
                }
                if (sens == 2)
                {
                    while (x0>=x1)
                    {
                        board[x0--][y0--]+=1;
                    }
                }
                if (sens == 3)
                {
                    while (x0>=x1)
                    {
                        board[x0--][y0++]+=1;
                    }
                }
                if (sens == 4)
                {
                    while (x0<=x1)
                    {
                        board[x0++][y0--]+=1;
                    }
                }
            }
            else
            {
                printf("\n");
            }     
        }
    
    }

    int overlapingPoints = 0;
    
    for (int i =0; i<XMAX; i = i+1)
    {
        for (int j=0; j<YMAX; j=j+1) 
        {
            if (board[i][j] > 1)
            {
                overlapingPoints++;
            }
        }
    }

    printf("nombres de points overlaping partie 1 ou 2 = %d\n",overlapingPoints);

    fclose(myfile);
    return 0;
}


