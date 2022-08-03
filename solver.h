int search(struct graph *g, int n)
{
    struct graph *aux=g;
    while ((*(*aux).v).num!=n)
        aux=(*aux).next;
    return (*(*aux).v).col;
}

void solution1(struct graph *g, int v, int *n)
{
    struct graph *aux=g;
    struct list_vertex *aux1;
    int id[v],i;
    while (g!=NULL)
    {
        aux1=(*(*g).v).next;
        for (i=0;i<=(*n);i++)
            id[i]=0;
        while (aux1!=NULL)
        {
            if ((*aux1).num<(*(*g).v).num)
            id[search(aux,(*aux1).num)]=1;
            aux1=(*aux1).next;
        }
        for (i=0;i<=(*n);i++)
            if (id[i]==0)
                (*(*g).v).col=i;
        if ((*(*g).v).col==-1)
        {
            (*n)++;
            (*(*g).v).col=(*n);
        }
        g=(*g).next;
    }
    g=aux;
}
