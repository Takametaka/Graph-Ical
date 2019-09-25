#ifndef _GRAPH_H
#define _GRAPH_H

#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include "list.h"

struct s_Node
{
    int id;
    int color;
    int data;
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

void displayGraph_sf(sfRenderWindow *window, Graph g);

//Chance of a link in percent
#define LINK_CHANCE 3

//Min and max weights (W_MIN <= W_MAX)
#define W_MIN 0
#define W_MAX 10

//Graph size
#define G_SIZE 50

//Node Radius
#define N_RADIUS 8

//Screen Size
#define SCREEN_Y 720

#define SCREEN_X 1180

//Node Consts
#define BASE_COLOR 1
#define DEPTH_COLOR 3
#define NO_DATA 0

#endif
