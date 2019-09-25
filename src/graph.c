#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include "graph.h"

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
    n->color = BASE_COLOR;
    n->data = NO_DATA;
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
    B->arcs = appendList(B->arcs,A);
    //A->weights = appendList(A->weights,weight);
}

void connectGraph(Graph g)
{
    //displayList(g->nodes);
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
        ptr->coord = (sfVector2f){ x , y };

        tmp = tmp->next;
    }
}


// Affiche le graphe
void displayGraph_sf(sfRenderWindow *window, Graph g)
{
	sfCircleShape *circle[g->size];
	for(int i = 0; i < g->size; i++)
	{
		//setting the nodes
		circle[i] = sfCircleShape_create();
		sfCircleShape_setRadius(circle[i],N_RADIUS);

		sfVector2f center = {N_RADIUS,N_RADIUS};
		sfCircleShape_setOrigin(circle[i],center);

		sfCircleShape_setPosition(circle[i],((Node)getListData(g->nodes,i))->coord);
	}


	for(int i = 0; i < g->size; i++)
	{
        Node I = getListData(g->nodes,i);
        
        //get color
        sfColor c = (I->color == 1 ? sfWhite : sfColor_fromRGB(73*I->color,277*I->color,137*I->color) );

        /*
        switch(I->color)
        {
            case 1 : c = sfRed; break;
            case 2 : c = sfGreen; break;
            case 3 : c = sfBlue; break;
            case 4 : c = sfYellow; break;
            case 5 : c = sfMagenta; break;
            case 6 : c = sfCyan; break;
            case 7 : c = sfWhite; break;
            default : c = sfColor_fromRGB(64,64,64);
        }
        */
        sfCircleShape_setFillColor(circle[i],c);

		for(int j = 0; j < g->size; j++)
		{
            Node J = getListData(g->nodes,j);

			int rv = (linked(I,J) || linked(J,I));
			if(rv)
			{	
				sfVector2f A = I->coord;
				sfVector2f B = J->coord;
				
				sfVertex line[2];
				line[0].position = A;
				line[1].position = B;
                
                //line[0].color = sfColor_fromRGB(255,200,0);
                //line[1].color = sfColor_fromRGB(255,200,0);
                line[0].color = c;
                line[1].color = c;

				sfRenderWindow_drawPrimitives(window,line,2,sfLines,NULL);
			}
		}
	}

	for(int i = 0; i < g->size; i++)
	{
		sfRenderWindow_drawCircleShape(window,circle[i],NULL);
		sfCircleShape_destroy(circle[i]);
	}

}
