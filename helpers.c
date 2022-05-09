/*
    Name: Karanvir Basson
    Title: Dijkstra's Algorithm
    Date: 05-08-2022
*/

#include "dijkstra.h"

int getAdjacencyMatrix(int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a file containing an adjacency matrix and store it in 2d array

    FILE* file = fopen(FILENAME, "r"); //Open file for reading

    if (file == NULL) { //If file doesn't exist

        printf("%s not found!\n", FILENAME);
        return 0;

    }
    
    for (int i = 0; i < NUM_NODES; i++) { //Initialize matrix to all zeores

        for (int j = 0; j < NUM_NODES; j++) {

            adjacencyMatrix[i][j] = 0;

        }

    }

    int size = ((NUM_NODES * 2) + 2) * sizeof(char); //Get size of string contining row of matrix
    char matrixRow[size]; //Initialize string contining row of matrix

    int i = 0; //Row index

    while (fgets(matrixRow, size, file)) { //Read matrix

        int j = 0;//Column index
        char* entry = strtok(matrixRow, " \n"); //Get current matrix entry as string

        while (entry != NULL) { //If string entry is not null

            adjacencyMatrix[i][j] = atoi(entry); //Convert string to int
            entry = strtok(NULL, " \n"); //Get next entry
            j++;

        }

        i++;

    }

    fclose(file); //Close file ptr
    return 1;

}

int connectNodes(Node* nodes[NUM_NODES], int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a list of nodes and an adjacency matrix, create graph edges

    for (int i = 0; i < NUM_NODES; i++) { //For all rows in matrix

        for (int j = 0; j < NUM_NODES; j++) { //For all columns in matrix

            if (adjacencyMatrix[i][j]) { //If edge exists

                if (nodes[i] -> edges == NULL) { //If no edges currently in list

                    nodes[i] -> edges = createEdge(nodes[j], adjacencyMatrix[i][j]); //Create edge
                    if (nodes[i] -> edges == NULL) return 0; //NULL ptr check

                } else { //if edges already exist

                    Edge* temp = nodes[i] -> edges; //Temp pointer to first edge

                    while (temp -> next != NULL) { //Get last edge

                        temp = temp -> next;

                    }

                    temp -> next = createEdge(nodes[j], adjacencyMatrix[i][j]); //Create edge
                    if (temp -> next == NULL) return 0; //NULL ptr check

                }

            }

        }

    }

    return 1; //Return 1, indicating success

}

Node* createNode(int ID) { //Given an id, create a node with that id


    Node* node = malloc(sizeof(Node)); //Allocate memory
    if (node == NULL) return NULL; //NULL ptr check

    //Initialize Node
    node -> ID = ID;
    node -> visited = 0;
    node -> edges = NULL;

    return node; //Return node


}

void freeNode(Node* node) { //Given a node, free it

    if (node == NULL) return; //NULL ptr check

    //FREE NODE EDGES
    while (node -> edges != NULL) {

        Edge* temp = node -> edges;
        node -> edges = node -> edges -> next;
        free(temp);

    }

    //FREE NODE
    free(node);

}

Edge* createEdge(Node* dest, int weight) { //Given a destination, create edge

    if (dest == NULL) return NULL; //NULL ptr check

    Edge* edge = malloc(sizeof(Edge)); //Allocate struct
    if (edge == NULL) return NULL; //NULL ptr check

    //INITIALIZE EDGE
    edge -> weight = weight;
    edge -> dest = dest;
    edge -> next = NULL;

    return edge; //Return newly allocated edge

}

int dijkstras(Node* nodes[NUM_NODES], int sourceIndex, int destIndex) { //Run Dijkstra's Algorithm and return shortest distance length

    int estimatedDistances[NUM_NODES]; //Array of estimated distances from source to each node

    for (int i = 0; i < NUM_NODES; i++) { //Initialize estimated distances

        estimatedDistances[i] = INF_VAL; //Set each distance to infinity

    }

    estimatedDistances[sourceIndex] = 0; //Initialize distance from source to source as 0

    Node* previousStack[NUM_NODES];
    int prevStackIndex = 0;

    for (int i = 0; i < NUM_NODES; i++) { //Initialize previousStack

        previousStack[i] = NULL;

    }

    Node* current = nodes[sourceIndex]; //Set current node as source
    current -> visited = 1; //Set source to visited

    previousStack[prevStackIndex++] = current; //Initialize prev stack index
    int currentTravelDist = 0;

    while (prevStackIndex > 0) { //While not all nodes visited

        printf("\nCurrently at node %d\n", current -> ID);
        
        printf("\nTRAVERSAL STACK:\n");

        for (int i = (prevStackIndex - 1); i >= 0; i--) { //For all items in traversal stack

            printf("NODE %d\n", previousStack[i] -> ID);

        }

        Edge* edge = current -> edges; //Get edges of current node

        Edge* next = NULL; //Edge for closest unvisited node
        int closestDist = INF_VAL; //Value of smallest edge from current node, initialized to infinity

        while (edge != NULL) { //For all edges

            int update = currentTravelDist + (edge -> weight); //Find distance from source to the node adjacent to current node
            int index = edge -> dest -> ID; //Get index of node adjacent to current node

            if (update < estimatedDistances[index]) { //If estimated distance entry should be updated

                estimatedDistances[index] = update;

            }

            if ((edge -> dest -> visited) == 0 && (edge -> weight) < closestDist) { //If it is the smallest edge encountered so far whose destination is unvisited

                closestDist = edge -> weight;
                next = edge; //Set as next edge to visit

            }

            edge = edge -> next;

        }

        if (next != NULL) { //If an edge to an unvisited node exists
            
            current = next -> dest; //Go to next node
            previousStack[prevStackIndex++] = current; //Add new node to traversal stack

        } else { //If no edge to an unvisited node exists
            
            current = previousStack[--prevStackIndex]; //Go to previous node 

        }

        current -> visited = 1; //Set next node as visited 
        currentTravelDist = estimatedDistances[current -> ID]; //Update total travel distance

        printf("\n");

        for (int i = 0; i < NUM_NODES; i++) { //Print estimated distances chart

            printf("NODE %d -> Estimated distance: %d\n", nodes[i] -> ID, estimatedDistances[i]);

        }

        printf("\nGoing to node %d\n", current -> ID);

    }

    printf("\nShortest distance from node %d to node %d is %d!\n\n", nodes[sourceIndex] -> ID, nodes[destIndex] -> ID, estimatedDistances[destIndex]);
    return estimatedDistances[destIndex]; //Return shortest distance from source to destination

}
