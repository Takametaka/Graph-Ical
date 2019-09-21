CC=gcc
CFLAGS=-Ofast -Wall -Wextra -Werror -g
SFLAGS=-lcsfml-graphics -lcsfml-window -lcsfml-system

run: graphical.out
	./$<

mem-test: graphical.out
	valgrind --leak-check=full --show-leak-kinds=all --log-file=log.txt ./$<

graph.o: src/graph.c include/graph.h 
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

force.o: src/force.c include/force.h include/graph.h 
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

list.o: src/list.c include/list.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

graphical.out: src/main.c include/*.h graph.o force.o list.o
	$(CC) $(CFLAGS) $< -o $@ -I./include graph.o force.o list.o $(SFLAGS) -lm


clean:
	rm -f *.o *.out *.zip

edit:
	vim -p Makefile src/main.c include/graph.h src/graph.c include/list.h src/list.c include/force.h src/force.c

# Pour installer les dépendances
install:
	sudo apt install gcc libcsfml-dev
