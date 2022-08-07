struct vert
{
    int val;
    struct vert *next;
};

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

struct vert *create_list(int **g,int v)
{
    struct vert *aux,*l=malloc(v*sizeof(*l));
    int i,j;
    (*l).val=0;
    for (j=0;j<v;j++)
    {
        if (g[0][j]==1)
            (*l).val++;
        (*l).val<<=1;
    }
    (*l).val>>=1;
    (*l).next=NULL;
    aux=l;
    for (i=1;i<v;i++)
    {
        struct vert *tmp=malloc(v*sizeof(*tmp));
        (*tmp).val=0;
        for(j=0;j<v;j++)
        {
            if (g[i][j]==1)
                (*tmp).val++;
            (*tmp).val<<=1;
        }
        (*tmp).val>>=1;
        (*tmp).next=NULL;
        (*aux).next=tmp;
        aux=(*aux).next;
    }       
    return l;
}

int counter(int res)
{
    int c=0;
    while (res!=0)
    {
        if (res%2!=0)
            c++;
        res>>=1;
    }
    return c;
}

void connection(int **g,struct vert *l,int v)
{
    struct vert *aux,*tmp;
    int i,j;
    for (i=0;i<v-1;i++)
    {
        aux=l;    
        for (j=i+1;j<v;j++)
        {
            aux=(*aux).next;
            if (g[i][j]==0)
            {
                g[i][j]=counter((*l).val&(*aux).val);
                g[j][i]=g[i][j];
            }
        }
        tmp=l;
        l=(*l).next;
        free(tmp);
   }
   free(l);
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
            (*aux).val+=abs(g[i][j]);
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
    struct vert *l=create_list(g,v);
    int i,j;
    struct rating *aux,*r=create_r(v);
    intersection(g,v);
    connection(g,l,v);
    filling_r(g,v,r);
    for (i=0;i<v;i++)
    {
        for (j=0;j<v;j++)
        {
            printf("%d ",g[i][j]); 
        }
        printf("\n");
    }
    aux=r;
    sort_r(aux);
    while (r!=NULL)
    {
        printf("%d-%d\n",(*r).vert,(*r).val);
        r=(*r).next;
    }
}
