/*
--- Day 6: Lanternfish ---

The sea floor is getting steeper. Maybe the sleigh keys got carried this way?

A massive school of glowing lanternfish swims past. They must spawn quickly 
to reach such large numbers - maybe exponentially quickly? You should model 
their growth rate to be sure.

Although you know nothing about this specific species of lanternfish, you 
make some guesses about their attributes. Surely, each lanternfish creates 
a new lanternfish once every 7 days.

However, this process isn't necessarily synchronized between every lanternfish 
- one lanternfish might have 2 days left until it creates another lanternfish, 
while another might have 4. So, you can model each fish as a single number that 
represents the number of days until it creates a new lanternfish.

Furthermore, you reason, a new lanternfish would surely need slightly longer 
before it's capable of producing more lanternfish: two more days for its first cycle.

So, suppose you have a lanternfish with an internal timer value of 3:

    After one day, its internal timer would become 2.
    After another day, its internal timer would become 1.
    After another day, its internal timer would become 0.
    After another day, its internal timer would reset to 6, and it would create 
    a new lanternfish with an internal timer of 8.
    After another day, the first lanternfish would have an internal timer of 5,
     and the second lanternfish would have an internal timer of 7.

A lanternfish that creates a new fish resets its timer to 6, not 7 (because 0 
is included as a valid timer value). The new lanternfish starts with an internal 
timer of 8 and does not start counting down until the next day.

Realizing what you're trying to do, the submarine automatically produces a list 
of the ages of several hundred nearby lanternfish (your puzzle input). 
For example, suppose you were given the following list:

3,4,3,1,2

This list means that the first fish has an internal timer of 3, the second fish 
has an internal timer of 4, and so on until the fifth fish, which has an internal 
timer of 2. Simulating these fish over several days would proceed as follows:

Initial state: 3,4,3,1,2
After  1 day:  2,3,2,0,1
After  2 days: 1,2,1,6,0,8
After  3 days: 0,1,0,5,6,7,8
After  4 days: 6,0,6,4,5,6,7,8,8
After  5 days: 5,6,5,3,4,5,6,7,7,8
After  6 days: 4,5,4,2,3,4,5,6,6,7
After  7 days: 3,4,3,1,2,3,4,5,5,6
After  8 days: 2,3,2,0,1,2,3,4,4,5
After  9 days: 1,2,1,6,0,1,2,3,3,4,8
After 10 days: 0,1,0,5,6,0,1,2,2,3,7,8
After 11 days: 6,0,6,4,5,6,0,1,1,2,6,7,8,8,8
After 12 days: 5,6,5,3,4,5,6,0,0,1,5,6,7,7,7,8,8
After 13 days: 4,5,4,2,3,4,5,6,6,0,4,5,6,6,6,7,7,8,8
After 14 days: 3,4,3,1,2,3,4,5,5,6,3,4,5,5,5,6,6,7,7,8
After 15 days: 2,3,2,0,1,2,3,4,4,5,2,3,4,4,4,5,5,6,6,7
After 16 days: 1,2,1,6,0,1,2,3,3,4,1,2,3,3,3,4,4,5,5,6,8
After 17 days: 0,1,0,5,6,0,1,2,2,3,0,1,2,2,2,3,3,4,4,5,7,8
After 18 days: 6,0,6,4,5,6,0,1,1,2,6,0,1,1,1,2,2,3,3,4,6,7,8,8,8,8

Each day, a 0 becomes a 6 and adds a new 8 to the end of the list, while each 
other number decreases by 1 if it was present at the start of the day.

In this example, after 18 days, there are a total of 26 fish. After 80 days, 
there would be a total of 5934.

Find a way to simulate lanternfish. How many lanternfish would there be after 80 days?

--- Part Two ---

Suppose the lanternfish live forever and have unlimited food and space. 
Would they take over the entire ocean?

After 256 days in the example above, there would be a total of 26984457539 lanternfish!

How many lanternfish would there be after 256 days?
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PART1 1
#define PART2 2
#define XMAX 1000
#define MAXDAYPART1 80
#define MAXDAYPART2 256

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

List *initialize(int first_number)
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

    FILE* myfile = fopen("day6.txt","r");
    if (myfile == NULL)
	{
		printf("file not available");
		return 0;
	}

    List * fishes = NULL;
    char * token = NULL;
    char dataline[XMAX];

    switch(part)
    {
        case PART1 :            

            fgets(dataline,1000,myfile);
            printf("dataline = %s\n",dataline);
            token = strtok(dataline,",");
            fishes = initialize(strtol(token,NULL,10));

            printf("liste des poissons lanterne :\n");
            showList(fishes);
            printf("----------------------------\n");

            while (token != NULL)
            {
                token = strtok(NULL,",");
                if (token != NULL) insertList(fishes,strtol(token,NULL,10));
            }
            printf("liste des poissons lanterne :\n");
            showList(fishes);
            printf("----------------------------\n");

            for (int day = 0; day<MAXDAYPART1; day++)
            {
                node *current = fishes->first;
                while (current != NULL)
                {
                    if (current->number > 0) current->number--;
                    else 
                    {
                        current->number = 6;
                        insertList(fishes,8);
                    }
                    current = current->next;
                }
                printf("jour %d\t nbnodes = %d\n",day,fishes->nbnode);
                //showList(fishes);
            }  
            

            printf("resultat de la partie 1 : %d\n",fishes->nbnode);
            break;


        case PART2 :

            fgets(dataline,1000,myfile);
            printf("dataline = %s\n",dataline);
            token = strtok(dataline,",");
            
            unsigned long long int fishes[9] = {0,0,0,0,0,0,0,0,0};
            unsigned long long int deadFishes;
            int current_age = 0;

            current_age = atoi(token);
            fishes[current_age] += 1;

            while (token != NULL)
            {
                token = strtok(NULL,",");
                current_age = atoi(token);
                if (token != NULL) fishes[current_age] += 1;
            }
            
            printf("liste des poissons lanterne :\n");
            for (int i=0;i<9;i++) printf("%lld\t",fishes[i]);
            printf("----------------------------\n");

            for (int day = 0; day<MAXDAYPART2; day++)
            {
                
                deadFishes = fishes[0];
                for (int i = 0; i<8; i++)
                { 
                    fishes[i]=fishes[i+1]
                }
                
                fishes[8] = deadFishes;
                fishes[6]+= deadFishes;
                
                for (int i=0;i<9;i++) printf("%lld\t",fishes[i]);
                printf("\n");
            }   

        unsigned long long totalFishes = 0;
        for (int i = 0; i<9 ; i++)
        {
            totalFishes += fishes[i];   
        }
        
        printf("resultat de la partie 2 : %lld\n",totalFishes);
        break;
    }

    return 0;
}
