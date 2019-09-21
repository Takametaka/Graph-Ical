#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "force.h"

//Node Part
Node newNode(int id)
{
    Node n = (Node)malloc(sizeof(struct s_Node));
    if(n == NULL)
    {
        fprintf(stderr,"Failed to malloc Node\n");
        exit(EXIT_FAILURE);
    }
    
    n->id = id;
    n->coord = (sfVector2f){ 0 , 0 };
    n->arcs = newList();
    //n->weights = newList();
    
    return n;
}

void destroyNode(Node nd)
{
    if(nd == NULL) return;
    destroyList(nd->arcs);
    free(nd);
}

//Graph part
Graph newGraph(int size)
{
    Graph g = (Graph)malloc(sizeof(struct s_Graph));
    if(g == NULL)
    {
        fprintf(stderr,"Failed to malloc Graph\n");
        exit(EXIT_FAILURE);
    }
    
    g->size = size;
    g->nodes = newList();
    
    for(int i = 0; i < g->size; i++)
        g->nodes = appendList(g->nodes,(void *)newNode(i));
    
    connectGraph(g);

    return g;
}

int linked(Node A, Node B)
{
    if(A == NULL || B == NULL)
        return 0;
    
    List tmp = A->arcs;

    if(tmp->data == NULL) return 0;

    while(tmp != NULL)
    {
        Node ptr = (Node)tmp->data;
        if(ptr->id == B->id)
            return 1;
        tmp = tmp->next;
    }

    return 0;
}

void newArc(Node A, Node B)
{
    //weight = W_MIN + ( rand() / RAND_MAX ) * (W_MAX - W_MIN);
    A->arcs = appendList(A->arcs,B);
    //A->weights = appendList(A->weights,weight);
}

void connectGraph(Graph g)
{
    displayList(g->nodes);
    for(int i = 0; i < g->size; i++)
        for(int j = 0; j < g->size; j++)
            if(i != j)
                if( rand()%100 < LINK_CHANCE )
                    newArc(getListData(g->nodes,i), getListData(g->nodes,j));
}

void destroyGraph(Graph g)
{
    if(g == NULL) return;

    List l = g->nodes;
    //free all data of list
    while(g->nodes != NULL)
    {
        destroyNode((Node)g->nodes->data);
        g->nodes = g->nodes->next;
    }
    //free list itself
    destroyList(l);
    //free graph
    free(g);
}

void randomizeCoord(Graph g)
{
    List tmp = g->nodes;
    while(tmp != NULL)
    {
        Node ptr = (Node)tmp->data;
        double x = (double) ( N_RADIUS ) + rand()%( SCREEN_X - 2*N_RADIUS);
        double y = (double) ( N_RADIUS ) + rand()%( SCREEN_Y - 2*N_RADIUS);
        printf("%lf %lf\n",x,y);
        ptr->coord = (sfVector2f){ x , y };

        tmp = tmp->next;
    }
}
