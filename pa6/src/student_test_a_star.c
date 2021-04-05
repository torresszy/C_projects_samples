#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "util.h"
#include "a_star.h"

// YOUR HELPER FUNCTIONS (IF ANY) HERE

int main()
{
    graph_t *g = graph_create(4);
    node_create(g, 0, 'A', 1, 0);
    node_create(g, 1, 'B', 0, 0);
    node_create(g, 2, 'C', 0, 1);
    node_create(g, 3, 'D', 1, -1);
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 0, 2);
    add_edge(g, 2, 3);
    printf("distance is %f\n", a_star(g, 3, 0));
    graph_free(g);
}