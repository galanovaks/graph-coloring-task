struct rating
{
    int vert;
    int val;
    struct rating *next;
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
    int**pr;
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

void solution(int **g,int v)
{
    int i,j,n,k,m;
    int **coloring,*color,res=0;
    intersection(g,v);
    connection(g,v);
    int **prior=get_priority(g,v);
/*    for (i=0;i<v;i++)
    {
        for (j=0;j<v;j++)
            printf("%d ",g[i][j]);
        printf("\n");
    }*/
    int *p=vert_pr(prior,v);
/*    for (i=0;i<v;i++)
        printf("\n%d-%d\n",i,p[i]);*/
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
       /* for (k=0;k<v;k++)
        {
            for (m=0;m<v;m++)
                printf("%d ",coloring[m][k]);
            printf("\n");
        }
        printf("\n");*/
    }
    res++;
    printf("%d\n",res);/*
    for(i=0;i<v;i++)
    {
        for(j=0;j<v;j++)
            printf("%d ",coloring[j][i]);
        printf("\n");
    }
    for(i=0;i<v;i++)
        printf("%d-%d\n",i,color[i]);*/
}
