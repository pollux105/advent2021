/*--- Day 2: Dive! ---

Now, you need to figure out how to pilot this thing.

It seems like the submarine can take a series of commands like forward 1, down 2, or up 3:

    forward X increases the horizontal position by X units.
    down X increases the depth by X units.
    up X decreases the depth by X units.

Note that since you're on a submarine, down and up affect your depth, 
and so they have the opposite result of what you might expect.

The submarine seems to already have a planned course (your puzzle input). 
You should probably figure out where it's going. For example:

forward 5
down 5
forward 8
up 3
down 8
forward 2

Your horizontal position and depth both start at 0. The steps above would 
then modify them as follows:

    forward 5 adds 5 to your horizontal position, a total of 5.
    down 5 adds 5 to your depth, resulting in a value of 5.
    forward 8 adds 8 to your horizontal position, a total of 13.
    up 3 decreases your depth by 3, resulting in a value of 2.
    down 8 adds 8 to your depth, resulting in a value of 10.
    forward 2 adds 2 to your horizontal position, a total of 15.

After following these instructions, you would have a horizontal position of 15 and a depth of 10. 
(Multiplying these together produces 150.)

Calculate the horizontal position and depth you would have after following the planned course. 
What do you get if you multiply your final horizontal position by your final depth?

--- Part Two ---

Based on your calculations, the planned course doesn't seem to make any sense. 
You find the submarine manual and discover that the process is actually slightly more complicated.

In addition to horizontal position and depth, you'll also need to track a third value, aim, 
which also starts at 0. The commands also mean something entirely different than you first thought:

    down X increases your aim by X units.
    up X decreases your aim by X units.
    forward X does two things:
        It increases your horizontal position by X units.
        It increases your depth by your aim multiplied by X.

Again note that since you're on a submarine, down and up do the opposite of 
what you might expect: "down" means aiming in the positive direction.

Now, the above example does something different:

    - forward 5 adds 5 to your horizontal position, a total of 5. 
    Because your aim is 0, your depth does not change.
    - down 5 adds 5 to your aim, resulting in a value of 5.
    - forward 8 adds 8 to your horizontal position, a total of 13. 
    Because your aim is 5, your depth increases by 8*5=40.
    - up 3 decreases your aim by 3, resulting in a value of 2.
    - down 8 adds 8 to your aim, resulting in a value of 10.
    - forward 2 adds 2 to your horizontal position, a total of 15. 
    Because your aim is 10, your depth increases by 2*10=20 to a total of 60.

After following these new instructions, you would have a horizontal 
position of 15 and a depth of 60. (Multiplying these produces 900.)

Using this new interpretation of the commands, calculate the horizontal position 
and depth you would have after following the planned course. 
What do you get if you multiply your final horizontal position by your final depth?


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define XMAX    20
#define PART1   0
#define PART2   1

int part2count(FILE* datafile){
    
    int length = 0;
    int depth = 0;
    int aim = 0;
    int instant_length = 0;
    char dataline[XMAX];
    while (fgets(dataline, XMAX, datafile)!= NULL)
    {
        char direction[XMAX];
        char * token = strtok(dataline," ");
        strcpy(direction,token);
        token = strtok(NULL," ");
        instant_length = atoi(token);

        if (strcmp(direction,"forward")==0)
        {
            length+=instant_length;
            depth += aim * instant_length;
        }
        if (strcmp(direction,"up")==0)       aim-=atoi(token);
        if (strcmp(direction,"down")==0)     aim+=atoi(token);
    }
    return depth*length;
}

int part1count(FILE* datafile){
    
    int length = 0;
    int depth = 0;
    int instant_length = 0;
    char dataline[XMAX];
    while (fgets(dataline, XMAX, datafile)!= NULL)
    {
        char direction[XMAX];
        char * token = strtok(dataline," ");
        strcpy(direction,token);
        token = strtok(NULL," ");
        instant_length = atoi(token);

        if (strcmp(direction,"forward")==0)  length+=instant_length;
        if (strcmp(direction,"up")==0)       depth-=atoi(token);
        if (strcmp(direction,"down")==0)     depth+=atoi(token);
    }
    return depth*length;
}

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

    FILE* myfile = fopen("day2.txt","r");
    if (myfile == NULL)
	{
		printf("file not available");
		return 0;
	}

    switch(part)
    {
        case PART1 :
            printf("the depth x advance number is : %d\n",part1count(myfile));
            break;
        case PART2 :
            printf("the depth x advance number is : %d\n",part2count(myfile));
            break;
    }


}
