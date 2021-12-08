
#include <stdio.h>
#include <stdlib.h>

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

void insert(List *list, int newnumber)
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

void delete(List *list)
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

void remove_node_by_index(List *list,int index)
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


int main(){

    List * mylist = initialize(0);

    insert(mylist, 1);
    insert(mylist, 2);
    insert(mylist, 3);

    showList(mylist);
    invertList(mylist);

    //remove_node_by_index(mylist,3);


    showList(mylist);
    printf("nombre total de node(s) = %d\n",mylist->nbnode);
}











































