#include <stdlib.h>

struct list_vertex
{
    int num;
    int col;
    struct list_vertex *next;
};

struct graph
{
    struct list_vertex *v;
    struct graph *next;
};

struct graph *create_graph(int ver)
{
    int i;
    struct graph *tmp=malloc(sizeof(*tmp));
    (*tmp).v=malloc(sizeof((*(*tmp).v)));
    (*(*tmp).v).num=ver-1;
    (*(*tmp).v).col=-1;
    (*(*tmp).v).next=NULL;
    (*tmp).next=NULL;
    for (i=ver-2;i>=0;i--)
    {
        struct graph *aux=malloc(ver*sizeof(*aux));
        (*aux).v=malloc(ver*sizeof((*(*aux).v)));
        (*(*aux).v).num=i;
        (*(*aux).v).col=-1;
        (*(*aux).v).next=NULL;
        (*aux).next=tmp;
        tmp=aux;
    }
    return(tmp);
}

void output_graph(struct graph *g)
{
    struct graph *aux=g;
    struct list_vertex *tmp;
    while (g!=NULL)
    {   
        tmp=(*g).v;
        printf("%d %d ",(*tmp).num,(*tmp).col);
        /*
        tmp=(*tmp).next;
        while (tmp!=NULL)
        {
            printf("%d ",(*tmp).num);
            tmp=(*tmp).next;
        }
        printf("\n");
        */
        g=(*g).next;
    }
    g=aux;
}

void add_edge(struct graph *g,int v1,int v2)
{
    struct graph *aux=g;
    struct list_vertex *tmp;
    struct list_vertex *tmp1;
    while ((*(*g).v).num!=v1)
        g=(*g).next;
    tmp=(*g).v;
    while ((*tmp).next!=NULL)
        tmp=(*tmp).next;
    tmp1=malloc(sizeof(*tmp1));
    (*tmp1).num=v2;
    (*tmp1).col=-1;
    (*tmp1).next=NULL;
    (*tmp).next=tmp1;
    g=aux;
}
