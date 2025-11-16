/**
 * FILE: DIJKSTRA.C
 * 
 * THIS FILE  CONTAINS EMPTY / DO-NOTHING IMPLEMENTATIONS
 * FOR THE FUNCTIONS REQUIRED OF DIJKSTRA'S ALGORITHM 
 *
 * DO NOT RENAME THESE FUNCTIONS OR CHANGE THEIR RETURN
 * TYPES OR INPUT PARAMETERS.
 *
 * YOU NEED TO COMPLETE THE IMPLEMENTATION OF THESE
 * FUNCTIONS. 
 *
 * THESE FUNCTIONS RECEIVE INPUT PARAMETERS THAT WILL
 * PROVIDE THEM WITH THE INFORMATION THAT THEY REQUIRE. 
 *
 * THE FUNCTIONS RETURN VALUES TO REPRESENT SUCCESS, ERROR,
 * OR, IN SOME CASES, DATA THAT HAS TO BE RETURNED. THE CALLER 
 * OF THESE FUNCTIONS WILL EXPECT TO RECEIVE THESE RETURN VALUES 
 * IN ORDER TO VERIFY THE OUTCOME OF THE FUNCTION CALL. 
 *
 * IF THERE ARE ANY FUNCTIONS THAT YOU DON'T HAVE TIME TO 
 * IMPLEMENT, PLEASE LEAVE THE EMPTY / DO-NOTHING IMPLEMENTATION
 * FOR THEM IN THIS FILE, OTHERWISE YOUR PROGRAM WON'T COMPILE
 * WHEN IT IS FED INTO OUR TESTER PROGRAM.
 * 
 */

/** 
 * ### INCLUDES
 */
#include <stddef.h>
#include "adj_matrix.h" // provides the definition of the 'Adjacency Matrix' struct which is required for one of the functions below
#include "dijkstra.h"   // provides the definition of structs and functions for the Dijkstra implementation
#include "core_definitions.h" // provides the definition of constants used across the project   

/** #### FUNCTION IMPLEMENTATIONS ## */

static int find_min_unvisited(DijkstraTable *pTable) {
    int minDist= VERY_LARGE_NUMBER;
    int min_index = -1;
    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        if (!pTable->table[i].visited && pTable->table[i].distance < minDist) {
            minDist = pTable->table[i].distance;
            min_index = i;
        }
    }
    return min_index;
}

/**
 * This function should perform the Dijkstra algorithm. It expects to receive a 
 * ready-made graph to work with in the form of an AdjacencyMatrix. It 
 * also expects to receive an empty DijkstraTable which will be pre-initialised and 
 * ready to use. It also expects to receive the starting node on the graph to commence 
 * the algorithm from. 
 * 
 * This function should implement the algorithm, running it on the graph 
 * provided and updating the DijkstraTable with the outcome. After the function 
 * is called, the DijkstraTable will be inspected to determine whether the 
 * algorithm has been completed successfully. 
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int runDijsktraAlgorithm(AdjacencyMatrix *pMatrix, DijkstraTable *pTable, int startNode)
{
    if (pMatrix == NULL|| pTable== NULL) return INVALID_INPUT_PARAMETER;
    if (startNode < 0 || startNode >= NUMBER_OF_VERTICES) return INVALID_INPUT_PARAMETER;

    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        pTable->table[i].visited = false;
        pTable->table[i].distance = VERY_LARGE_NUMBER;
        pTable->table[i].predecessor = -1;
    }

    pTable->table[startNode].distance = 0;
    pTable->table[startNode].predecessor = -1;

    for (int iter =0; iter < NUMBER_OF_VERTICES -1; iter++) {
        int u = find_min_unvisited(pTable);
        if (u == -1) break;
        pTable->table[u].visited = true;

        for (int v =0; v < NUMBER_OF_VERTICES; v++) {
           int w = pMatrix->matrix[u][v];
           if (w<=0) continue;
           if (pTable->table[u].distance == VERY_LARGE_NUMBER) continue;

           int alt = pTable ->table[u].distance + w;
              if (alt < pTable->table[v].distance) {
                pTable->table[v].distance = alt;
                pTable->table[v].predecessor = u;
              }
        }
    }
   
    return SUCCESS;
}


/**
 * This function should determine the shortest path that exists on a graph 
 * from a given starting node (nodeFrom) to a given end node (nodeTo). 
 * The function expects to receive a pre-populated DijkstraTable which already 
 * contains the outcome of running the Dijkstra algorithm on a graph. It will 
 * also be provided with an array (pathFound) into which the shortest path should 
 * be recorded. The path should be recorded in reverse order; showing, from the 
 * end node, the predecessors that lead us there from the start node. 
 * For example, if the shortest path on graph from node 2 to node 8 was found 
 * to be 2 -> 4 -> 5 -> 8. The content that would be recorded in the ‘pathFound’ 
 * variable would be as follows: [8][5][4][2]. I.e., it shows the relevant nodes 
 * in the path, in reverse order. This includes the start and end node too. After the 
 * function is called, the 'pathFound' will be inspected to determine whether the 
 * algorithm has been completed successfully. 
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int getShortestPathFrom(DijkstraTable *pTable, int nodeFrom, int nodeTo, int pathFound[])
{
    if (pTable ==NULL || pathFound == NULL) return INVALID_INPUT_PARAMETER;
    if (nodeFrom < 0 || nodeFrom >= NUMBER_OF_VERTICES) return INVALID_INPUT_PARAMETER;
    if (nodeTo < 0 || nodeTo >= NUMBER_OF_VERTICES) return INVALID_INPUT_PARAMETER;

    if (pTable->table[nodeTo].distance == VERY_LARGE_NUMBER) return FAILURE;

    for (int i=0; i <NUMBER_OF_VERTICES; i++) pathFound[i] = -1;
    int index =0;
    int current = nodeTo;
    while(current != -1 && index < NUMBER_OF_VERTICES) {
        pathFound[index++] = current;
        if (current == nodeFrom) break;
        current = pTable->table[current].predecessor;
    }
    if (pathFound[index -1] != nodeFrom) 
    {
        return FAILURE;
    }

    return SUCCESS;
}