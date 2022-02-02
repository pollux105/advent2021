/*--- Day 3: Binary Diagnostic ---

The submarine has been making some odd creaking noises, 
so you ask it to produce a diagnostic report just in case.

The diagnostic report (your puzzle input) consists of a list of binary numbers which, 
when decoded properly, can tell you many useful things about the conditions of the submarine. 
The first parameter to check is the power consumption.

You need to use the binary numbers in the diagnostic report to generate two new 
binary numbers (called the gamma rate and the epsilon rate). The power consumption 
can then be found by multiplying the gamma rate by the epsilon rate.

Each bit in the gamma rate can be determined by finding the most common bit in the 
corresponding position of all numbers in the diagnostic report. 
For example, given the following diagnostic report:

00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010

Considering only the first bit of each number, there are five 0 bits and seven 1 bits. 
Since the most common bit is 1, the first bit of the gamma rate is 1.

The most common second bit of the numbers in the diagnostic report is 0, 
so the second bit of the gamma rate is 0.

The most common value of the third, fourth, and fifth bits are 1, 1, and 0, 
respectively, and so the final three bits of the gamma rate are 110.

So, the gamma rate is the binary number 10110, or 22 in decimal.

The epsilon rate is calculated in a similar way; rather than use the most common bit, 
the least common bit from each position is used. So, the epsilon rate is 01001, or 9 in decimal. 
Multiplying the gamma rate (22) by the epsilon rate (9) produces the power consumption, 198.

Use the binary numbers in your diagnostic report to calculate the gamma rate and 
epsilon rate, then multiply them together. What is the power consumption of 
the submarine? (Be sure to represent your answer in decimal, not binary.)

--- Part Two ---

Next, you should verify the life support rating, which can be determined by multiplying the 
oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found 
in your diagnostic report - finding them is the tricky part. Both values are located using 
a similar process that involves filtering out values until only one remains. 
Before searching for either rating value, start with the full list of binary numbers from 
your diagnostic report and consider just the first bit of those numbers. Then:

    Keep only numbers selected by the bit criteria for the type of rating value for which 
    you are searching. Discard numbers which do not match the bit criteria.
    If you only have one number left, stop; this is the rating value for which you are searching.
    Otherwise, repeat the process, considering the next bit to the right.

The bit criteria depends on which type of rating value you want to find:

    To find oxygen generator rating, determine the most common value (0 or 1) in the current 
    bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally 
    common, keep values with a 1 in the position being considered.
    To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit 
    position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, 
    keep values with a 0 in the position being considered.

For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

    Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) 
    than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
    Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), 
    so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
    In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
    In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
    In the fifth position, there are an equal number of 0 bits and 1 bits (one each). 
    So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
    As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.

Then, to determine the CO2 scrubber rating value from the same example above:

    Start again with all 12 numbers and consider only the first bit of each number. 
    There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
    Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), 
    so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
    In the third position, there are an equal number of 0 bits and 1 bits (one each). 
    So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
    As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.

Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and 
CO2 scrubber rating, then multiply them together. 

What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define XMAX    14
#define XMAXI   1000
#define PART1   0
#define PART2   1
#define BINARY_LENGTH   11

typedef struct node node;
typedef struct List List;

struct node
{
    int number;
    node * next;
};

struct List
{
    node *first;
    int nbnode;
};

List * initialize(int first_number)
{
    List *list = malloc(sizeof(*list));
    node *node = malloc(sizeof(*node));

    if (list == NULL || node == NULL)
    {
        exit(EXIT_FAILURE);
    }

    node->number = first_number;
    node->next = NULL;
    list->first = node;
    list->nbnode = 1;

    return list;
}

void insertList(List *list, int newnumber)
{
    /* Création du nouvel élément */
    node *new = malloc(sizeof(*new));
    if (list == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new->number = newnumber;

    /* Insertion de l'élément au début de la liste */
    new->next = list->first;
    list->first = new;
    list->nbnode=list->nbnode + 1;
}

void deleteList(List *list)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (list->first != NULL)
    {
        node *toDelete = list->first;
        list->first = list->first->next;
        free(toDelete);
    }
}

void removeIndexList(List *list,int index)
{
    int count = 0;
    
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (index > 0)
    {
        node *current = list->first;
        node * toDelete = NULL;
    
        while (count < (index-1))
        {
            current = current->next;
            count++;
        } 
        printf("nombre courant = %d\n",current->number);
        toDelete = current->next;
        current->next = toDelete->next;
        list->nbnode=list->nbnode-1;
        free(toDelete);
    }
    else
    {
        node *toDelete = list->first;
        list->first = list->first->next;
        free(toDelete);
        list->nbnode = list->nbnode -1;
    }
}

void showList(List *list)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    node *current = list->first;

    while (current != NULL)
    {
        printf("%d -> ", current->number);
        current = current->next;
    }
    printf("NULL\n");
}

void invertList(List *list)
{
    node * prevNode = list->first;
    list->first=list->first->next;
    node * curNode = list->first;

    prevNode->next = NULL;
    
    while(list->first!=NULL)
    {
        list->first = list->first->next;
        curNode->next = prevNode;
        prevNode = curNode;
        curNode = list->first;
    }
    list->first = prevNode;
}


int part1count(FILE* datafile)
{
    int Er = 0;
    int Gr = 0;
    int lines_number = 0;
    int tab[XMAX];
    int j = 0;
    char dataline[XMAX];

    for (j=0;j<XMAX;j++)
    {
        tab[j] = 0;
    }
    j = 0;
            
    while(fgets(dataline,XMAX,datafile)!=NULL)
    {
        while(dataline[j] != '\0')
        {
            tab[j] += (dataline[j] -'0');
            
            
            j++;
        }
        j= 0; 
        lines_number++;
    }

    int compteur;
    for (compteur=0; compteur<XMAX-2;compteur++)
    {
        if (tab[compteur] < (lines_number /2))
        { 
            tab[compteur] = 0 + '0';
        }
        else
        {
            tab[compteur] = 1 + '0';
        }
    }

    int power = 1;
    compteur = 0;
    while (XMAX-3-compteur >= 0)
    { 
       Er += (tab[XMAX-3-compteur]-'0')*power;
       Gr += (1-(tab[XMAX-3-compteur]-'0'))*power;
       power *= 2;
       compteur++;
    }

    return Gr*Er;
}

int part2count(FILE* datafile)
{
    
    List * binaryReport = NULL;
    int lines_number = 0;
    int uns = 0;
    int zeros = 0;
    char dataline[XMAXI];
    int column_offset = 0;
    int lines_number_buffer;
    int firstline = 1;
    int side = NULL;


    // get list from file -- invert it and show it
    // -------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------
    while(fgets(dataline,XMAX,datafile)!=NULL)
    {
        char *ptr;
        if (firstline == 1)
        {
            binaryReport = initialize(strtol(dataline, &ptr, 2));
            firstline = 0;
        }
        else
        {       
            insertList(binaryReport,strtol(dataline, &ptr, 2));
            lines_number++;       
        }
    }

    invertList(binaryReport);
    showList(binaryReport);
    // -------------------------------------------------------------------------------
    
    // get maximum between one and zeros
    // ---------------------------------------------------------------------------
    // ---------------------------------------------------------------------------
    while((BINARY_LENGTH-column_offset >=0) && binaryReport->nbnode > 1){

        node *current = binaryReport->first;

        // recherche des zero / uns
        // ---------------------------------------------------------------------------
        // ---------------------------------------------------------------------------
        while (current != NULL)
        {
            if(current->number & (1 << (BINARY_LENGTH-column_offset))) uns++;
            else zeros++;

            current = current->next ;
        }
        printf("uns = %d\tzeros = %d\tnbligne = %d\n",uns, zeros,binaryReport->nbnode);
        side = (zeros<=uns) ? 0 : 1;
        zeros = 0;
        uns = 0;
        
        // elimination des nombres en minorite
        // ---------------------------------------------------------------------------
        // ---------------------------------------------------------------------------
        current = binaryReport->first;
        node * prevNode = binaryReport->first;
        printf("firstnode = %d\n",current->number);
        node * toDelete = NULL;
        
        
        while (current != NULL)
        {
            if (side){
                if(!(current->number & (1 << (BINARY_LENGTH-column_offset))))
                {
                    prevNode->next = current->next;
                    toDelete = current;
                    //printf("nombre a effacer = %d\n",toDelete->number);
                    if (binaryReport->first == current) 
                    {
                        binaryReport->first = current->next;
                    }
                    current = current->next;
                    free(toDelete);
                    binaryReport->nbnode = binaryReport->nbnode-1;
                }
                else
                {
                    prevNode = current;
                    current = current->next;
                }
            }
            else
            {
                if(current->number & (1 << (BINARY_LENGTH-column_offset)))
                {
                    prevNode->next = current->next;
                    toDelete = current;
                    if (binaryReport->first == current) 
                    {
                        binaryReport->first = current->next;
                    }
                    current = current->next;
                    free(toDelete);
                    binaryReport->nbnode = binaryReport->nbnode-1;
                }
                else
                {
                    prevNode = current;
                    current = current->next;
                }
            }
        }

        showList(binaryReport);
        
        column_offset+=1;
    }

    


}  


int main(int argc, char *argv[])
{

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

    FILE* myfile = fopen("day3.txt","r");
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
