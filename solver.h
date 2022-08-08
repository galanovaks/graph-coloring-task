struct cycle
{
    int vert;
    int loyal;
    struct cycle *next;
};

void connection(int **g,int v)
{
    int i,j,n;
    for (i=0;i<v-1;i++)  
        for (j=i+1;j<v;j++)
            for (n=0;n<v;n++)
                if ((g[i][n]==-2)&&(g[i][n]==g[j][n])&&(g[i][j]!=-2))
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
/*
int **get_priority_rec(int **pr)
{
    int i,j,n,m,f;
    int *pr;    
    for (i=0;i<v;i++)
    {
        for (n=0;n<v;n++)
        {
            for (j=0;j<v;j++)
            {
                if (g[i][j]==n)
                {
                    pr[i][n]++;
                    m--;
                }
                if ((f==0)&&(g[i][j]<0))
                    m--;
            }
        }
    }
    return pr;
}

int *vert_pr(int **pr,int v)
{
    int i,j,n,w,c,s;
    int *p=malloc(v*sizeof(int));
    for (i=0;i<v;i++)
        p[i]=-1;
    for (i=0;i<v;i++)
    {
        w=0;
        for (j=0;j<v;j++)
        {
            for (n=0;((n<v)&&(pr[i][n]==pr[j][n]));n++);
            if (n<v)
            {
                if (pr[i][n]>=pr[j][n])
                    w++;
            }
            else
                w++;
        }
        c=v-w;
        for (s=0;s<v;s++)
        {
            if ((s>=c)&&(p[s]==-1))
            {
                p[s]=i;
                break;
            }
        }
    }
       return p;
}
*/
void add_vert_cyc(struct cycle *c,int **g,int n)
{
    struct cycle *tmp=c;
    int f=0;
    while (((*tmp).next!=NULL)&&(f==0))
    {
        if (g[(*tmp).vert][n]!=-2)
            f++;
        tmp=(*tmp).next;
    }
    if ((f==0)&&(g[(*tmp).vert][n]==-2))
    {

        struct cycle *aux=malloc(sizeof(int));
        (*aux).vert=n;
        (*aux).next=NULL;
        (*tmp).next=aux;
    }
    else
        (*c).loyal=-1;
}

void delete_c(struct cycle *c)
{
    struct cycle *tmp;
    while (c!=NULL)
    {
        tmp=(*c).next;
        free(c);
        c=tmp;
    }
}

struct cycle *max_comp_g(int **g,int v,int *a,int *nofut)
{
    int i,j,n,s1,s2;
    struct cycle *res=malloc(sizeof(int));
    (*res).vert=-1;
    (*res).next=NULL;
    s1=-1;
    for (i=0;i<v;i++)
    {   
        if (a[i]!=1)
            continue;
        for (j=0;j<v;j++)
        {
            if (a[j]!=1)
                continue;
            struct cycle *aux=malloc(sizeof(int));
            (*aux).vert=i;
            (*aux).next=NULL;
            s1=0;
            if (g[i][j]==-2)
            {    
                struct cycle *tmp=malloc(sizeof(int));
                (*tmp).vert=j;
                (*tmp).next=NULL;
                (*aux).next=tmp;
                s2=1;
                for (n=0;n<v;n++)
                {   
                    if (a[n]!=1)
                        continue;
                    if  ((g[i][n]==-2)&&(g[j][n]==-2))
                    {
                        (*aux).loyal=1;
                        add_vert_cyc(aux,g,n);
                        if ((*aux).loyal==1)
                            s2++;
                    }
                }
                if (s2>1)
                {
                    if (s2>s1)
                    {
                        tmp=res;
                        res=aux;
                        delete_c(tmp);
                    }
                    else
                    {
                        delete_c(tmp);
                    }
                }
                else
                {
                    a[i]=0;
                    a[v]--;
                    nofut[i]=1;
                    nofut[v]++;
                }
            }
        }
    }
    return res;
}

void solution(int **g,int v)
{
    int i,j,n,k,m;
    intersection(g,v);
    connection(g,v);
    int *appl,*nofut,*fin;
    appl=malloc((v+1)*sizeof(int));
    nofut=malloc((v+1)*sizeof(int));
    fin=malloc((v+1)*sizeof(int));
    for (i=0;i<v;i++)
        appl[i]=1;
    for (i=0;i<v;i++)
    {
        fin[i]=0;
        nofut[i]=0;
    }
    appl[v]=v;
    nofut[v]=0;
    fin[v]=0;
    struct cycle *c=max_comp_g(g,v,appl,nofut);
    while(c!=NULL)
    {
        printf("*%d*",(*c).vert);
        c=(*c).next;
    }
/*    int **coloring,*color,res=0;
    connection(g,v);
    int **pr;
    pr=malloc(v*sizeof(int*));
    for (i=0;i<v;i++)
    {
        pr[i]=malloc(v*sizeof(int));
        for (j=0;j<v;j++)
            pr[i][j]=0;
    }
    int *p=vert_pr(prior,v);
    coloring=malloc(v*sizeof(int*));
    for (i=0;i<v;i++)
    {   
        coloring[i]=malloc(v*sizeof(int));
        for (j=0;j<v;j++)
            coloring[i][j]=0;
    }
    color=malloc(v*sizeof(int));
    for (n=0;n<v;n++)
    {
        for(i=0;coloring[p[n]][i]==1;i++);   
        coloring[p[n]][i]=2;
        color[p[n]]=i;
        for(j=0;j<v;j++)
            if (g[p[n]][j]==-2)
                coloring[j][i]=1;
        if (res<i)
            res=i;
        for (i=0;i<v;i++)
        printf("%d\n",p[n]);
        for (k=0;k<=res;k++)
        {
            for (m=0;m<v;m++)
                printf("%d ",coloring[m][k]);
            printf("\n");
        }
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
        printf(" %d-%d;",i,color[i]);*/
}
