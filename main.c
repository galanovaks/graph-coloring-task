#include <stdio.h>
#include "graph.h"
#include "solver.h"

int main()
{
    int v,e,i,v1,v2;
    scanf("%d %d",&v,&e);
    struct graph *g=create_graph(v);
    for(i=0;i<e;i++)
    {
        scanf("%d %d",&v1,&v2);
        add_edge(g,v1,v2);
        add_edge(g,v2,v1);
    }
    output_graph(g);
    return 0;
}
