dijkstra: dijkstra.o helpers.o
	clang -Wall -pedantic -std=c99 dijkstra.o helpers.o -o dijkstra

dijkstra.o: dijkstra.c dijkstra.h
	clang -Wall -pedantic -std=c99 -c dijkstra.c -o dijkstra.o

helpers.o: helpers.c dijkstra.h
	clang -Wall -pedantic -std=c99 -c helpers.c -o helpers.o

clean:
	rm *.o
