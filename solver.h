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

int **get_priority(int **g,int v)
{
    int i,j,n,m,f;
    int **pr;    
    pr=malloc(v*sizeof(int*));
    for (i=0;i<v;i++)
    {
        pr[i]=malloc(v*sizeof(int));
        for (j=0;j<v;j++)
            pr[i][j]=0;
    }
    for (i=0;i<v;i++)
    {
        f=0;
        m=v;
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
            if (m==0)
                break;
            f=1;
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
    int i,j,n,s1,s2,s_i;
    struct cycle *res=malloc(sizeof(int));
    (*res).vert=-1;
    (*res).next=NULL;
    s1=-1;
    for (i=0;i<v;i++)
    {   
        s_i=0;
        if (a[i]!=1)
            continue;
        for (j=0;j<v;j++)
        {
            if (a[j]!=1)
                continue;
            if (a[i]!=1)
                break;
            struct cycle *aux=malloc(sizeof(int));
            (*aux).vert=i;
            (*aux).next=NULL;
            s2=0;
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
                if (s2>s_i)
                    s_i=s2;
                if (s2>=2)
                {
                    if (s2>s1)
                    {
                        tmp=res;
                        res=aux;
                        delete_c(tmp);
                    }
                    else
                    {
                        delete_c(aux);
                    }
                }
            }
        }
        if (s_i<2)
        {
            a[i]=0;
            a[v]--;
            nofut[i]=1;
            nofut[v]++;
        }
    }
    return res;
}

void solution(int **g,int v)
{
    int i,j,n,k,m,count=0;
    intersection(g,v);
    connection(g,v);
    int *appl,*nofut,*fin;
    appl=malloc((v+1)*sizeof(int));
    nofut=malloc((v+1)*sizeof(int));
    for (i=0;i<v;i++)
    {
        appl[i]=1;
        nofut[i]=0;
    }
    appl[v]=v;
    nofut[v]=0;
    struct cycle *tmp,*c=max_comp_g(g,v,appl,nofut);
    int **coloring,*color,res=0;
    int **pr=get_priority(g,v);
    int *p=vert_pr(pr,v);
    int **p_c=malloc(2*sizeof(int*));
    for (i=0;i<2;i++)
        p_c[i]=malloc(v*sizeof(int));
    for(i=0;i<v;i++)
    {
        p_c[0][p[i]]=i;
        p_c[1][i]=0;
    }
    coloring=malloc(v*sizeof(int*));
    for (i=0;i<v;i++)
    {   
        coloring[i]=malloc(v*sizeof(int));
        for (j=0;j<v;j++)
            coloring[i][j]=0;
    }
    color=malloc(v*sizeof(int));
    while (count!=v)
    {
        if ((*c).vert!=-1)
        {
            tmp=c;
            while (tmp!=NULL)
            {
                p_c[1][(*tmp).vert]=1;
                appl[(*tmp).vert]=0;
                appl[v]--;
                tmp=(*tmp).next;
            }
        }
        else
        {
            for (i=0;i<v;i++)
                if (nofut[i]==1)
                    p_c[1][i]=1;
        }
        for (i=0;i<v;i++)
            if (p_c[1][p[i]]==1)
        {
            count++;      
            p_c[1][p[i]]=-1;
            for(n=0;coloring[p[i]][n]==1;n++);   
            coloring[p[i]][n]=2;
            color[p[i]]=n;
            for(j=0;j<v;j++)
                if (g[p[i]][j]==-2)
                    coloring[j][n]=1;
            if (res<n)
                res=n;

/*            for (k=0;k<=res;k++)
            {
                for (m=0;m<v;m++)
                    printf("%d ",coloring[m][k]);
                printf("\n");
            }
            printf("\n");*/
        }
        c=max_comp_g(g,v,appl,nofut);
    }
    res++;
    printf("%d\n",res);
/*    for(i=0;i<res;i++)
    {
        for(j=0;j<v;j++)
            printf("%d ",coloring[j][i]);
        printf("\n");
    }
    for(i=0;i<v;i++)
        printf(" %d-%d;",i,color[i]);*/
}
