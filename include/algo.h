#ifndef _ALGO_H
#define _ALGO_H

#include "graph.h"

void composantesConnexes(Graph g);

void parcoursProfondeur(Graph g,sfRenderWindow *win);

void displayMenu(sfRenderWindow *window);

#define MENU_X 100

#define N_BOX 10

//Menu texts
#define MENU_1 "newGraph"
#define MENU_2 "Composantes Connexes"
#define MENU_3 "Parcours en Profondeur"

#endif
