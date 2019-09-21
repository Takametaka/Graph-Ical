#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List newList()
{
    List l = (List)malloc(sizeof(struct s_List));
    if(l == NULL)
    {
        fprintf(stderr,"Failed to malloc List\n");
        exit(EXIT_FAILURE);
    }

    l->data = NULL;
    l->next = NULL;

    return l;
}

List appendList(List list,void *data)
{
    if(list == NULL)
        list = newList();
    if(list->data == NULL)
    {
        list->data = data;
        return list;
    }

    List rv = list;

    while(list->next != NULL)
        list = list->next;

    list->next = newList();
    list->next->data = data;
    
    return rv;
}

void *getListData(List list,int i)
{
    while(list != NULL && i > 0)
    {
        list = list->next;
        i--;
    }
    if(list == NULL)
    {
        fprintf(stderr,"Went to far in the list, no element there\n");
        exit(EXIT_FAILURE);
    }

    return list->data;
}

void destroyList(List list)
{
    if(list == NULL)
        return;

    List ptr;
    while(list->next != NULL)
    {
        ptr = list->next;
        free(list);
        list = ptr;
    }
    free(list);
}

void displayList(List l)
{
    printf("List :");
    while(l != NULL)
    {
        printf("\t|%2p|\n",l->data);
        l = l->next;
    }
    printf("\t|%p|\n",NULL);
}
