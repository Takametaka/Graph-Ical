#ifndef _GRAPH_H
# define _GRAPH_H

#include <SFML/System.h>
#include "list.h"

struct s_Node
{
    int id;
    sfVector2f coord;
    List arcs;
    //List weights;    
}; typedef struct s_Node * Node;

struct s_Graph
{
	int size;
    List nodes;
}; typedef struct s_Graph * Graph;

//Node Part
Node newNode(int id);

void destroyNode(Node nd);

//Graph part
Graph newGraph(int size);

void connectGraph(Graph g);

void newArc(Node A, Node B);

int linked(Node A, Node B);

void destroyGraph(Graph g);

void randomizeCoord(Graph g);

//Chance of a link in percent
#define LINK_CHANCE 5

//Min and max weights (W_MIN <= W_MAX)
#define W_MIN 0
#define W_MAX 10

#define G_SIZE 20

#endif
