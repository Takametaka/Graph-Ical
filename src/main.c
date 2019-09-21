#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "list.h"
#include "force.h"

int main()
{
    srand(getpid());
    Graph g = newGraph(G_SIZE);
    randomizeCoord(g);

    sfVideoMode mode = {SCREEN_X,SCREEN_Y,32};
    sfRenderWindow *window;
    sfEvent event;

    window = sfRenderWindow_create(mode, "Graph-ical", sfClose, NULL);
    if(!window)
        exit(EXIT_FAILURE);

    while(sfRenderWindow_isOpen(window))
    {
        while(sfRenderWindow_pollEvent(window,&event))
        {
            if(event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        
        sfRenderWindow_clear(window, sfBlack);
        displayGraph_sf(window,g);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);

    destroyGraph(g);

    return 0;
}
