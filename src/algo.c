#include <stdio.h>
#include <SFML/System.h>
#include "algo.h"
#include "graph.h"

/*
void displayMenu(sfRenderWindow *window)
{
    sfVertex line[2];

    line[0].position = (sfVector2f){SCREEN_X,SCREEN_Y}; line[1].position = (sfVector2f){SCREEN_X,0};
    line[0].color = sfWhite; line[1].color = sfWhite;
    
    sfRenderWindow_drawPrimitives(window,line,2,sfLines,NULL);

    for(int i = 0; i < SCREEN_Y; i += SCREEN_Y/N_BOX)
    {
        line[0].position = (sfVector2f){SCREEN_X,SCREEN_Y - i};
        line[1].position = (sfVector2f){SCREEN_X + MENU_X,SCREEN_Y - i};

        sfRenderWindow_drawPrimitives(window,line,2,sfLines,NULL);
    }

    sfText *text[N_BOX];
    char *name[N_BOX] = { MENU_1, MENU_2, MENU_3};
    for(int i = 0; i < N_BOX; i++)
    {
        text[i] = sfText_create();
        sfText_setString(text[i],name[i]);
        sfText_setCharacterSize(text[i],10);

        sfRenderWindow_drawText(window, text[i], NULL);
    }
}
*/

void composantesRec(Node n, int c)
{   
    if(n == NULL) return;
    if(n->color != 0) return;
    
    n->color = c;

    List l = n->arcs;
    while( (l != NULL) )
    {
        Node tmp = (Node)l->data;
        composantesRec(tmp,c);
        l = l->next;
    }
}

void setColor(Graph g,int c)
{
    List l = g->nodes;
    while( (l != NULL) && (l->data != NULL) )
    {
        ((Node)l->data)->color = c;
        l = l->next;
    }

}

void composantesConnexes(Graph g)
{
    setColor(g,0);
    List l = g->nodes;
    int c = 1;

    while( l != NULL )
    {
        Node tmp = (Node)l->data;
        if( tmp->color == 0 )
        {
            printf("Calling on %d with c = %d\n",tmp->id,c);
            composantesRec(tmp,c);
            c++;
        }
        l = l->next;   
    }

    printf("%d composantes connexes\n",c-1);
}

void recPronfondeur(Node n,Graph g,sfRenderWindow *win)
{
    if(n == NULL) return;
    if(n->color == DEPTH_COLOR) return;

    sfSleep(sfSeconds(0.05));

    n->color = DEPTH_COLOR;
    
    sfRenderWindow_clear(win, sfBlack);
    displayGraph_sf(win,g);
    sfRenderWindow_display(win);

    List l = n->arcs;
    while( (l != NULL) )
    {
        Node tmp = (Node)l->data;
        recPronfondeur(tmp,g,win);
        l = l->next;
    }
}

void parcoursProfondeur(Graph g,sfRenderWindow *win)
{
    setColor(g,BASE_COLOR);
    recPronfondeur((Node)g->nodes->data,g,win);
}
