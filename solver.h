struct cycle
{
    int vert;
    int loyal;
    struct cycle *next;
};

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

struct cycle *max_comp_g(int **g,int v,int *nofut,int *krasim)
{
    int i,j,n,s1,s2,s_i;
    struct cycle *res=malloc(sizeof(int));
    (*res).vert=-1;
    (*res).next=NULL;
    s1=-1;
    for (i=0;i<v;i++)
    {   
        s_i=0;
        if ((nofut[i]==1)||(krasim[i]==-1))
            continue;
        for (j=0;j<v;j++)
        {
            if ((nofut[j]==1)||(krasim[j]==-1))
                continue;
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
                    if ((nofut[n]==1)||(krasim[n]==-1))
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
                        s1=s2;
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
            nofut[i]=1;
        }
    }
    return res;
}

void pokras(int **g,int v,int *nofut,int *c,int **col,int *r,int i)
{
    int j,n;
    for(n=0;col[i][n]==1;n++);   
    col[i][n]=2;
    c[i]=n;
    for(j=0;j<v;j++)
        if (g[i][j]==-2)
    {
            col[j][n]=1;
            nofut[j]=1;
    }
    if (*r<n)                                                               
        *r=n;
//    printf("%d^%d\n",i,n);
}

void solution(int **g,int v)
{
//    output_graph_0(g,v);
    int i,j,n,count=0,f=0,size,k,m,min,minv,mink;
    intersection(g,v);
    int *nofut,*fin,*krasim=malloc(v*sizeof(int));
    fin=malloc(v*sizeof(int));
    nofut=malloc(v*sizeof(int));
    for (i=0;i<v;i++)
    {
        fin[i]=0;
        nofut[i]=0;
        krasim[i]=0;
    }
    struct cycle *tmp,*c=max_comp_g(g,v,nofut,krasim);
    int **coloring,*color,res=0;
    coloring=malloc(v*sizeof(int*));
    for (i=0;i<v;i++)
    {   
        coloring[i]=malloc(v*sizeof(int));
        for (j=0;j<v;j++)
            coloring[i][j]=0;
    }
    color=malloc(v*sizeof(int));
//    output_graph(g,v);
    while (count!=v)
    {
        if ((*c).vert!=-1)
        {
            size=0;
            tmp=c;
//            printf("\ncycle-");
            while (tmp!=NULL)
            {
                size++;
                if (krasim[(*tmp).vert]==0)
                {
                    krasim[(*tmp).vert]=-1;
                    count++;
                    pokras(g,v,nofut,color,coloring,&res,(*tmp).vert);
  /*                  for (k=0;k<=res;k++)
                    {
                        for (m=0;m<v;m++)
                            printf("%d ",coloring[m][k]);
                        printf("\n");
                    } */  
                }
                tmp=(*tmp).next;
            }
//            printf("\n");
        }
        else
        {   
            for (i=0;i<v;i++)
                if (krasim[i]!=-1)
                    for (j=0;j<v;j++)
                        if ((g[i][j]==-2)&&(krasim[j]!=-1))
                            krasim[i]++;
            for (i=0;i<v-count;i++)
            {   
                min=res+2;
                for (j=0;j<v;j++)
                {   
                    mink=0;
                    if (krasim[j]!=-1)
                    {
                        for (n=0;n<=res;n++)
                            if (coloring[j][n]==0)
                                mink++; 
                        if (min>mink)
                        {
                            min=mink;
                            minv=j;
                        }
                        if ((min==mink)&&(krasim[minv]<krasim[j]))
                            minv=j;
                    }          
                }
                for (j=0;j<v;j++)
                    if ((krasim[j]!=-1)&&(g[minv][j]==-2))
                        krasim[j]--;
                krasim[minv]=-1;
                count++; 
  //              printf("%d count %d\n",minv,count);
                for(n=0;coloring[minv][n]==1;n++);   
                coloring[minv][n]=2;
                color[minv]=n;
                for(j=0;j<v;j++)
                    if (g[minv][j]==-2)
                        coloring[j][n]=1;
                if (res<n)
                    res=n;
    /*        for (k=0;k<=res;k++)
            {
                for (m=0;m<v;m++)
                    printf("%d ",coloring[m][k]);
                printf("\n");
            }
            printf("\n");*/
            }
        }
        tmp=c;
        if ((*tmp).vert!=-1)
        {
            delete_c(tmp);
            c=max_comp_g(g,v,nofut,krasim);
        }
    }
    res++;
    printf("%d\n",res);
    for(i=0;i<v;i++)
    {
        for(j=0;j<v;j++)
            if (((g[i][j]==-2)||(g[i][j]==-3))&&(color[j]==color[i]))
                f=1;
    }
    if (f==0)
        printf("OK\n");
    else
        printf("FATAL ERROR\n");
    
/*    for(i=0;i<res;i++)
    {   
        for(j=0;j<v;j++)
            printf("%d ",coloring[j][i]);
        printf("\n");
    }
    for(i=0;i<v;i++)
        printf(" %d-%d;",i,color[i]);
*/}
