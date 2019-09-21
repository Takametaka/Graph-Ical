#ifndef _LIST_H
#define _LIST_H

struct s_List
{
    void *data;
    struct s_List *next;
};
typedef struct s_List *List;

List newList();

List appendList(List list,void *data);

void *getListData(List list,int i);

void destroyList(List list);

void displayList(List l);

#endif
