#include <stdlib.h>

struct list_vertex
{
    int num;
    int col;
    struct vertex *next;
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
    (*tmp).v=malloc(ver*sizeof((*(*tmp).v)));
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
    while (g!=NULL)
    {
        printf("%d %d\n",(*(*g).v).num,(*(*g).v).col);
        g=(*g).next;
    }
    g=aux;
}
