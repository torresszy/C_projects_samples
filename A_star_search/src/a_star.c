#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "util.h"
#include "a_star.h"

/********* GRAPH *********/

/* graph_create: create a graph
 *
 * Returns: a graph
 */ 
graph_t *graph_create(int num_nodes)
{
    graph_t* rv = (graph_t*)malloc(sizeof(graph_t));
    if (rv == NULL) {
        fprintf(stderr, "space allocation for graph failed\n");
        exit(1);
    }

    rv->num_nodes = num_nodes;
    rv->nodes = (node_t**)malloc(sizeof(node_t*) * num_nodes);
    if (rv->nodes == NULL) {
        fprintf(stderr, "space allocation for the nodes array failed\n");
        exit(1);
    }

    for (int i = 0; i < num_nodes; i++) {
        rv->nodes[i] = NULL;
    }

    return rv;
}

/* node_create: create a graph node
 *
 * graph: the graph
 * node_num: node number
 * city_name: the city
 * latitude: city latitude
 * longitude: city longitude
 * 
 */ 
void node_create(graph_t *graph, int node_num, char *city_name, 
                 double latitude, double longitude)
{    
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL) {
        fprintf(stderr, "space allocation for node %d failed\n", node_num);
        exit(1);
    }

    node->node_num = node_num;
    node->city_name = city_name;
    node->latitude = latitude;
    node->longitude = longitude;

    node->neighbors = NULL;
    node->parent = NULL;
    node->f_cost = 0;
    node->g_cost = 0;
    node->h_cost = 0;

    graph->nodes[node_num] = node;
}

/* add_neighbor: add a neighbor to the target node's
 *   linked list of neighbors
 *
 * node: the target node
 * neighbor_num: the number of the neighbor node to be added
 * 
 */ 
void add_neighbor(node_t* node, int neighbor_num)
{   
    intlist_t* neighbor = (intlist_t*)malloc(sizeof(intlist_t));
    if (neighbor == NULL) {
        fprintf(stderr, "space allocation for the neighbor failed\n");
        exit(1);
    }

    neighbor->num = neighbor_num;
    neighbor->next = NULL;

    if (node->neighbors == NULL) {
        node->neighbors = neighbor;
    } else {
        intlist_t* curr = node->neighbors;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = neighbor;
    }
}

/* add_edge: add an edge between two nodes
 *
 * graph: the graph
 * node_num1: the first node
 * node_num2: the second node
 * 
 */ 
void add_edge(graph_t* graph, int node_num1, int node_num2)
{   
    add_neighbor(graph->nodes[node_num1], node_num2);
    add_neighbor(graph->nodes[node_num2], node_num1);
}

/* free_intlist: free the neighbors intlist of a node
 *
 * node: the node
 */ 
void free_intlist(node_t* node)
{   
    if (node->neighbors) {
        intlist_t* curr = node->neighbors;
        intlist_t* prev;
        while (curr->next) {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
        free(curr);
    }
}

/* graph_free: free a graph and its nodes
 *
 * graph: the graph
 */ 
void graph_free(graph_t* graph)
{   
    if (graph) {
        for (int i = 0; i < graph->num_nodes; i++) {
            if (graph->nodes[i]) {
                free_intlist(graph->nodes[i]);
                free(graph->nodes[i]);
            }
        }
        free(graph->nodes);
        free(graph);
    }
}

/********* A* SEARCH *********/

/* euclidean_distance: calculate the euclidean distance 
 *   between two nodes
 *
 * node_1: the first node
 * node_2: the second node
 * 
 * Returns: the euclidean distance of the nodes
 */ 
double euclidean_distance(node_t* node_1, node_t* node_2)
{
    return sqrt(pow((node_1->latitude - node_2->latitude), 2) + 
                pow((node_1->longitude - node_2->longitude), 2));
}

/* add_node_to_open_set: add a node to the open set
 *
 * graph: the graph
 * open_set: a set of nodes to visit, stored in a priority queue and prioritized by f-cost
 * parent_node_num: the parent of the node to be added to the open set
 * curr_node_num: the node to be added to the open set
 * end_node_num: the ending node number
 * closed set: a set of visited nodes
 * 
 * Returns: true if the node is added to the open set, false otherwise
 */ 
bool add_node_to_open_set(graph_t* graph, queue_t* open_set, int parent_node_num, 
                          int curr_node_num, int end_node_num, set_t* closed_set)
{   
    double h_cost = euclidean_distance(graph->nodes[curr_node_num], graph->nodes[end_node_num]);
    double g_cost = graph->nodes[parent_node_num]->g_cost + 
                    euclidean_distance(graph->nodes[curr_node_num], graph->nodes[parent_node_num]);
    double f_cost = g_cost + h_cost;

    if (queue_query(open_set, curr_node_num)) {
        if (graph->nodes[curr_node_num]->f_cost < f_cost) {
            return false;
        }
    }

    if (set_query(closed_set, curr_node_num)) {
        return false;
    }

    graph->nodes[curr_node_num]->h_cost = h_cost;
    graph->nodes[curr_node_num]->g_cost = g_cost;
    graph->nodes[curr_node_num]->f_cost = f_cost;

    queue_add(open_set, curr_node_num, f_cost);
    return true;
    
}

/* add_neighbors_to_open_set: add the neighbors of a node to the open set
 *
 * graph: the graph
 * open_set: a set of nodes to visit, stored in a priority queue and prioritized by f-cost
 * parent_node_num: the parent whose neighbors are being added to the open set
 * end_node_num: the ending node number
 * closed set: a set of visited nodes
 */ 
void add_neighbors_to_open_set(graph_t* graph, queue_t* open_set, int parent_node_num, 
                               int end_node_num, set_t* closed_set)
{
    intlist_t* curr = graph->nodes[parent_node_num]->neighbors;

    while (curr) {
        if (add_node_to_open_set(graph, open_set, parent_node_num, curr->num, 
                                 end_node_num, closed_set)) {
            graph->nodes[curr->num]->parent = graph->nodes[parent_node_num];
        }
        curr = curr->next;
    }
    set_add(closed_set, parent_node_num);
}


/* a_star: performs A* search
 *
 * graph: the graph
 * start_node_num: the staring node number
 * end_node_num: the ending node number
 * 
 * Returns: the distance of the path between the start node and end node
 */ 
double a_star(graph_t *graph, int start_node_num, int end_node_num)
{
    set_t* closed_set = set_create();
    queue_t* open_set = queue_create();
    node_t* curr;

    graph->nodes[start_node_num]->g_cost = 0.0;
    graph->nodes[start_node_num]->h_cost = euclidean_distance(graph->nodes[start_node_num], 
                                                              graph->nodes[end_node_num]);
    graph->nodes[start_node_num]->f_cost = graph->nodes[start_node_num]->h_cost;

    queue_add(open_set, start_node_num, graph->nodes[start_node_num]->f_cost);

    while (!queue_is_empty(open_set)) {
        curr = graph->nodes[queue_remove(open_set)];
        if (curr == graph->nodes[end_node_num]) {
            queue_free(open_set);
            set_free(closed_set);
            return curr->g_cost;
        }
        
        add_neighbors_to_open_set(graph, open_set, curr->node_num, end_node_num, closed_set);
    }

    queue_free(open_set);
    set_free(closed_set);
    return -1;
}