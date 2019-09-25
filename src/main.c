#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "list.h"
#include "algo.h"

int main()
{
    srand(getpid());
    Graph g = newGraph(G_SIZE);
    randomizeCoord(g);

    sfVideoMode mode = {SCREEN_X + MENU_X,SCREEN_Y,32};
    sfRenderWindow *window;
    sfEvent event;

    window = sfRenderWindow_create(mode, "Graph-ical", sfClose, NULL);
    if(!window)
        exit(EXIT_FAILURE);
    int update = 1;
    //composantesConnexes(g);
    //parcoursProfondeur(g,window);
    while(sfRenderWindow_isOpen(window))
    {
        while(sfRenderWindow_pollEvent(window,&event))
        {
            if(event.type == sfEvtClosed)
                sfRenderWindow_close(window);

        }
        
        if(update)
        {  
            sfRenderWindow_clear(window, sfBlack);
            displayMenu(window);
            displayGraph_sf(window,g);
            sfRenderWindow_display(window);
            update = 1;
        }
    }
    sfRenderWindow_destroy(window);

    destroyGraph(g);

    return 0;
}
