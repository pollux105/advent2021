/*
--- Day 4: Giant Squid ---

You're already almost 1.5km (almost a mile) below the surface of the ocean, 
already so deep that you can't see any sunlight. What you can see, however, 
is a giant squid that has attached itself to the outside of your submarine.

Maybe it wants to play bingo?

Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. 
Numbers are chosen at random, and the chosen number is marked on all boards 
on which it appears. (Numbers may not appear on all boards.) If all numbers 
in any row or any column of a board are marked, that board wins. (Diagonals don't count.)

The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) 
pass the time. It automatically generates a random order in which to draw numbers 
and a random set of boards (your puzzle input). 
For example:

7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7

After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, 
but the boards are marked as follows (shown here adjacent to each other to save space):

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

Finally, 24 is drawn:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

At this point, the third board wins because it has at least one complete row 
or column of marked numbers (in this case, the entire top row is marked: 14 21 17 24 4).

The score of the winning board can now be calculated. Start by finding the 
sum of all unmarked numbers on that board; in this case, the sum is 188. 
Then, multiply that sum by the number that was just called when the board 
won, 24, to get the final score, 188 * 24 = 4512.

To guarantee victory against the giant squid, figure out which board will 
win first. What will your final score be if you choose that board?

--- Part Two ---

On the other hand, it might be wise to try a different strategy: let the giant squid win.
You aren't sure how many bingo boards a giant squid could play at once, so rather 
than waste time counting its arms, the safe thing to do is to figure out which 
board will win last and choose that one. That way, no matter which boards it picks, 
it will win for sure.

In the above example, the second board is the last to win, which happens after 13
is eventually called and its middle column is completely marked. If you were to keep 
playing until this point, the second board would have a sum of unmarked numbers equal 
to 148 for a final score of 148 * 13 = 1924.

Figure out which board will win last. Once it wins, what would its final score be?


*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define XMAX 500
#define PART1 1
#define PART2 2

int * PlayingTable = NULL;
int draft[200];
int numberOfBingoCards = 0;
int linesNumber = 0;
char dataline[XMAX];
int numero_stop = 0;
int card_stop = 0;
int result = 0;

int extractingCardNumber(char *filename);
void showTable(int *table,int numberOfTables);


int extractingCardNumber(char *filename){
    int linesNumber = 0;
    FILE* myfile = fopen(filename,"r");
    if (myfile == NULL)
	{
		printf("file not available");
		return 0;
	}
    while (fgets(dataline, XMAX, myfile)!= NULL) linesNumber++;
    fclose(myfile);
    return (linesNumber-1)/6;
}

void showTable(int *table,int numberOfTables)
{
    for (int i = 0; i<numberOfTables;i++){
        for (int j = 0; j < 5; ++j){
            for (int k = 0; k < 5; ++k){
                printf("%d\t", table[(i*25) + (j * 5) + k]);
            }
            printf("\n");
        }
        printf("\n");
    }
        
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

    numberOfBingoCards = extractingCardNumber("day4.txt");
    printf("nombre de cartes de bingo = %d\n",numberOfBingoCards);

    //creation de la table de jeu
    int *PlayingTable = malloc(sizeof(int[5][5])*numberOfBingoCards);
    
    if (PlayingTable == NULL)
    {
        printf("Échec de l'allocation\n");
        return EXIT_FAILURE;
    }

    linesNumber = 0;
    
    FILE* myfile = fopen("day4.txt","r");
    char *token;
    char *draftNumbers;
    int draftLength = 0;

    // recuperation du tirage
    int x = 0;
    fgets(dataline, XMAX, myfile);
    draftNumbers = strtok(dataline,",");
    draft[x] = strtol(draftNumbers,NULL,10);
    while (draftNumbers !=NULL)
    {
        draftNumbers = strtok(NULL,",");
        draft[++x]=strtol(draftNumbers,NULL,10);
        draftLength++;
    }
    linesNumber++;

    
    for (unsigned i = 0; i<numberOfBingoCards;i++)
    {
        for (unsigned j = 0; j < 5; )
        {
            fgets(dataline, XMAX, myfile);
            if (linesNumber >1 && linesNumber%6 != 1)
            {   
                //printf("ligne n : %d, i = %d, j = %d\t",linesNumber,i,j);printf("%s\n",dataline);
                for (unsigned k = 0; k < 5; )
                {
                    
                    token = strtok(dataline," ");
                    
                    PlayingTable[(i*25) + (j * 5) + k] = strtol(token,NULL,10);
                    k++;
                    while( token != NULL ) 
                    {
                        //printf( " %s\t", token);
                        token = strtok(NULL," ");
                        PlayingTable[(i*25) + (j * 5) + k] = strtol(token,NULL,10);
                        k++;
                    }
                    //printf("\n");
                }
                
                j++;
            }
            linesNumber++;     
        }
    }
      

    showTable(PlayingTable,numberOfBingoCards);

    printf("draftLength = %d\n",draftLength);
    for (x = 0;x<draftLength;x++) printf("%d ",draft[x]);
    printf("\n");
    
    int vertical_sum = 0;
    int horizontal_sum = 0;
    int winningCards = 0;

    switch(part)
    {
        case PART1 :
            
            for (x = 0;x<draftLength;x++){
                //elimination des nombres trouves
                for (int i = 0; i<numberOfBingoCards; i++){
                    for (int j = 0; j < 5; ++j){
                        for (int k = 0; k < 5; ++k){
                            if (PlayingTable[i*25+(j*5)+k] == draft[x]) 
                            {
                                PlayingTable[i*25+(j*5)+k] = 0;
                            }
                        }
                    }
                }
        
                printf("%d was drawn !\n",draft[x]);
                showTable(PlayingTable,numberOfBingoCards);
                printf("\n\n");
            
                int vertical_sum = 0;
                int horizontal_sum = 0;

                //calcul des sommes des verticales et horizontales
                for (int i = 0; i<numberOfBingoCards; i++){
                    for (int j = 0; j < 5; ++j){
                        for (int k = 0; k < 5; ++k) horizontal_sum += PlayingTable[i*25+(j*5)+k];
                        if (horizontal_sum == 0)
                        {
                            printf("jeu horizontal\n");
                            numero_stop = draft[x];
                            card_stop = i;
                            goto endThisGame;
                        }
                        else
                        {
                            horizontal_sum = 0;
                        }   
                    }
                }

                for (int i = 0; i<numberOfBingoCards;i++)
                    for (int k = 0; k < 5; ++k)
                        for (int j = 0; j < 5; ++j)
                        {
                            vertical_sum += PlayingTable[i*25+(j*5)+k];
                            card_stop = i;
                        }
                        if (vertical_sum == 0)
                        {
                            printf("jeu vertical\n");
                            numero_stop = draft[x];
                            goto endThisGame;
                        }
                        else
                        {
                            vertical_sum = 0;
                        }       
            }
        break;
     
        
        case PART2 :
            

            
            for (x = 0;x<draftLength;x++){
                //elimination des nombres trouves
                for (int i = 0; i<numberOfBingoCards; i++){
                    for (int j = 0; j < 5; ++j){
                        for (int k = 0; k < 5; ++k){
                            if (PlayingTable[i*25+(j*5)+k] == draft[x]) 
                            {
                                PlayingTable[i*25+(j*5)+k] = 0;
                            }
                        }
                    }
                }
        
                printf("%d was drawn !\n",draft[x]);
                //showTable(PlayingTable,numberOfBingoCards);
                printf("\n\n");
            


                //calcul des sommes des verticales et horizontales
                for (int i = 0; i<numberOfBingoCards; i++){
                    for (int j = 0; j < 5; ++j){
                        for (int k = 0; k < 5; ++k)
                        {
                            horizontal_sum += PlayingTable[i*25+(j*5)+k];
                        }
                        if (horizontal_sum == 0)
                        {
                            numero_stop = draft[x];
                            card_stop = i;
                            printf("cartes gagnantes = %d\n",winningCards++);
                            if (winningCards == numberOfBingoCards) goto endThisGame;
                            for (int j = 0; j < 5; ++j)
                            {
                                for (int k = 0; k < 5; ++k)
                                {
                                    PlayingTable[i*25+(j*5)+k] = 100;   
                                }
                            }      
                        }
                        else
                        {
                            horizontal_sum = 0;
                        }   
                    }
                }

                for (int i = 0; i<numberOfBingoCards;i++){
                    for (int k = 0; k < 5; ++k){
                        for (int j = 0; j < 5; ++j)
                        {
                            vertical_sum += PlayingTable[i*25+(j*5)+k];
                            card_stop = i;
                        }
                        if (vertical_sum == 0)
                        {
                            numero_stop = draft[x];
                            card_stop = i;
                            printf("cartes gagnantes = %d\n",winningCards++);
                            if (winningCards == numberOfBingoCards) goto endThisGame;
                            for (int j = 0; j < 5; ++j)
                            {
                                for (int k = 0; k < 5; ++k)
                                { 
                                    PlayingTable[i*25+(j*5)+k] = 100;
                                }
                            }
                                                     
                        }
                        else
                        {
                            vertical_sum = 0;
                        }       
                    }
                }
            }
        break;

    endThisGame : printf("voila ! arrete a %d = %d\n",x,draft[x]);

            for (unsigned j = 0; j < 5; ++j){
                for (unsigned k = 0; k < 5; ++k){
                    result += PlayingTable[(card_stop*25) + (j * 5) + k];
                }
            }
            result = result * numero_stop;
            printf("the result for part%d is : %d\n",part,result);
    break;
    
    }
    return 0;
}
