struct rating
{
    int vert;
    int val;
    struct rating *next;
};

struct rating *create_r(int v)
{
    int i;
    struct rating *res=malloc(sizeof(*res));
    (*res).vert=v-1;
    (*res).val=0;
    (*res).next=NULL;
    for (i=v-2;i>=0;i--)
    {   
        struct rating *aux=malloc(sizeof(*aux));
        (*aux).vert=i;
        (*aux).val=0;
        (*aux).next=res;
        res=aux;
    }
    return res;
}

void connection(int **g,int v)
{
    int i,j,n;
    for (i=0;i<v-1;i++)  
        for (j=i+1;j<v;j++)
            for (n=0;n<v;n++)
                if ((g[i][n]<0)&&(g[i][n]==g[j][n]))
                {
                    g[i][j]++;
                    g[j][i]++;
                }
}

void intersection(int **g,int v)
{
    int i,j;
    for (i=0;i<v;i++)
        g[i][i]=-1;
    for (i=0;i<v;i++)
        for(j=0;j<v;j++)
            if (g[i][j]==1)
                g[i][j]=-2;
}

void filling_r(int **g, int v, struct rating *r)
{
    int i,j;
    struct rating *aux=r;
    for (i=0;i<v;i++)
    {
        for (j=0;j<v;j++)
            if (g[i][j]!=0)
            (*aux).val++;
        aux=(*aux).next;
    }
}

void change (int *i, int *j)
{
    *i+=*j;
    *j=*i-*j;
    *i=*i-*j;
}

void sort_r (struct rating *r)
{
    struct rating *aux=(*r).next;
    while (aux!=NULL)
    {
        if ((*r).val>(*aux).val)
        {
            change(&(*r).val,&(*aux).val);
            change(&(*r).vert,&(*aux).vert);
        }
        aux=(*aux).next;
    }
    if ((*r).next!=NULL)
        sort_r((*r).next);
}

void solution(int **g,int v)
{
    int i,j,k,k1,k2;
    struct rating *aux,*r=create_r(v);
    int **coloring,*color,res=0;
    intersection(g,v);
    printf("*");
    connection(g,v);
    printf("*");
    filling_r(g,v,r);
    printf("*");
    aux=r;
    sort_r(aux);
    aux=r;
    while(aux!=NULL)
    {
        printf("%d-%d\n",(*aux).vert,(*aux).val);
        aux=(*aux).next;
    }
    coloring=malloc(v*sizeof(int*));
    for (i=0;i<v;i++)
    {   
    k=0;k1=0;k2=0;
        coloring[i]=malloc(v*sizeof(int));
        for (j=0;j<v;j++)
        {
            coloring[i][j]=0;
            printf("%d ",g[i][j]);
            if (g[i][j]==0)
            k++;
            if (g[i][j]==1)
            k1++;
            if (g[i][j]==2)
            k2++;
        }
        printf("\n%d-%d,%d,%d\n",i,k,k1,k2);
    }
    color=malloc(v*sizeof(int));
    while (r!=NULL)
    {
        for(i=0;coloring[(*r).vert][i]!=0;i++);   
        coloring[(*r).vert][i]=2;
        color[(*r).vert]=i;
        for(j=0;j<v;j++)
            if (g[(*r).vert][j]==-2)
                coloring[j][i]=1;
        if (res<i)
            res=i;
        r=(*r).next;
    }
    res++;
    printf("%d\n",res);
    for(i=0;i<res;i++)
    {
        for(j=0;j<v;j++)
            printf("%d ",coloring[j][i]);
        printf("\n");
    }
    for(i=0;i<v;i++)
        printf("%d-%d\n",i,color[i]);
}
