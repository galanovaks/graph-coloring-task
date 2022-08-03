#include <stdio.h>
#include "graph.h"
#include "solver.h"

int main()
{
    int v;
    scanf("%d", &v);
    struct graph *g=create_graph(v);
    output_graph(g);
    output_graph(g);
    return 0;
}
