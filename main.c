#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "solver.h"

int main()
{
    int v,e,j;
    char files[36][7]={"4_1","20_1","20_3","20_5","20_7","20_9",
    "50_1","50_3","50_5","50_7","50_9","70_1","70_3","70_5",
    "70_7","70_9","100_1","100_3","100_5","100_7","100_9",
    "250_1","250_3","250_5","250_7","250_9","500_1","500_3",
    "500_5","500_7","500_9","1000_1","1000_3","1000_5","1000_7",
    "1000_9"};
    FILE *f;
/*    for(j=0;j<36;j++)
    {*/
        f=fopen(files[1],"r");
        fscanf(f,"%d %d",&v,&e);
        int **g=create_graph(v,e,f);
        printf("%s-",files[1]);
        output_graph(g,v);
        printf("\n");
        fclose(f);
        solution(g,v);
   /* }*/
    return 0;
}
