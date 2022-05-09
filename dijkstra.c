/*
    Name: Karanvir Basson
    Title: Dijkstra's Algorithm
    Date: 05-08-2022
*/

#include "dijkstra.h"

int main() {

    int adjacencyMatrix[NUM_NODES][NUM_NODES]; //Integer matrix representing adjacency matrix
    int res = getAdjacencyMatrix(adjacencyMatrix); //Initialize adjacency matrix from file
    if (res == 0) return -1; //If file read doesn't work

    Node* nodes[NUM_NODES]; //Array of nodes in graph

    for (int i = 0; i < NUM_NODES; i++) { //Create all nodes in array

        nodes[i] = createNode(i); //Create node
        if (nodes[i] == NULL) return -1; //If node creation fails

    }

    res = connectNodes(nodes, adjacencyMatrix); //Connect all nodes using adjacency matrix
    if (res == 0) return -1; //If node connection fails

    dijkstras(nodes, 0, 1); //Run Dijkstra's Algorithm

    for (int i = 0; i < NUM_NODES; i++) { //For all nodes

        freeNode(nodes[i]); //Free current node

    }

    return 1;

}
