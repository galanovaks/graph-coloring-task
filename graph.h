int **create_graph(int ver,int eg,FILE *f)
{   
    int **graph,c,i,j;
    graph=malloc(ver*sizeof(int*));
    for (i=0;i<ver;i++)
    {
        graph[i]=malloc(ver*sizeof(int));
        for (j=0;j<ver;j++)
            graph[i][j]=0;
    }  
    for (c=0;c<eg;c++)
    {
        fscanf(f,"%d %d",&i,&j);
        graph[i][j]=1;
        graph[j][i]=1;
    }
    return graph;
}

void output_graph(int **graph,int ver)
{
    int i,j;
    for (i=0;i<ver;i++)
    {
        printf("%d-",i);
        for (j=0;j<ver;j++)
            if (graph[i][j]==1)
                printf("%d,",j);
        printf("\n");
            
    }
}
