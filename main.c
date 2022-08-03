#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "solver.h"

int main()
{
    int v,e,i,v1,v2,n,j;
    char files[36][7]={"4_1","20_1","20_3","20_5","20_7","20_9",
    "50_1","50_3","50_5","50_7","50_9","70_1","70_3","70_5",
    "70_7","70_9","100_1","100_3","100_5","100_7","100_9",
    "250_1","250_3","250_5","250_7","250_9","500_1","500_3",
    "500_5","500_7","500_9","1000_1","1000_3","1000_5","1000_7",
    "1000_9"};
    FILE *fp;
    for(j=0;j<36;j++)
    {
        fp=fopen(files[j],"r");
        fscanf(fp,"%d",&v);
        fscanf(fp,"%d",&e);
        struct graph *g=create_graph(v);
        for(i=0;i<e;i++)
        {
            fscanf(fp,"%d",&v1);
            fscanf(fp,"%d",&v2);
            add_edge(g,v1,v2);
            add_edge(g,v2,v1);
        }
        fclose(fp);
        solution1(g,v,&n);
        n++;
        printf("%s %d\n",files[j],n);
    }
    return 0;
}
