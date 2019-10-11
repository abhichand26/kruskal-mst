#include<stdio.h>
#include<stdlib.h>
#define M 20

/*
** Program to find minimum spanning tree using Kruskal Algorithm with Union-Find method
** Made by - Abhishek Chand
*/

int parent[M],rank[M];

typedef struct EDGE
{
	int u;
	int v;
	int w;
}Edge;

void swap(Edge *x,Edge *y)
{
	Edge temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

void printMST(Edge *T,int n)
{
	int i,cost=0;
	printf("Selected Edges:\nu  v  w\n");
	for(i=0;i<n;i++)
	{
		printf("%d  %d  %d\n",T[i].u,T[i].v,T[i].w);
		cost+=T[i].w;
	}
	printf("\nCost = %d",cost);
}

int partition(Edge *A,int beg,int end)
{
	int i,p=beg,pivot=A[end].w;
	for(i=beg;i<end;i++)
	{
		if(A[i].w<=pivot)
		{
			swap(&A[i],&A[p]);
			p++;
		}
	}
	swap(&A[end],&A[p]);
	return p;
}

void QuickSort(Edge *A,int beg,int end)
{
	int q;
	if(beg>=end)
		return;
	q=partition(A,beg,end);
	QuickSort(A,beg,q-1);
	QuickSort(A,q+1,end);
	
}

int find(int u)
{
	int i=0,A[M];
	while(u!=parent[u])
	{
		A[i]=u;
		u=parent[u];
		i++;
	}
	i--;
	while(i>=0)
	{
		parent[A[i]]=u;
		i--;
	}
	return u;
}

void unionbyrank(int u, int v)
{
	int x,y;
	x=find(u);
	y=find(v);
	if(rank[x]<rank[y])
		parent[x]=y;
	else if(rank[y]<rank[x])
		parent[y]=x;
	else
	{
		parent[x]=y;
		rank[y]++;
	}
}

void Kruskal(Edge *E,int n,int e)
{
	int i,j,x,y,u,v;
	Edge *T;
	T=(Edge*)malloc((n-1)*sizeof(Edge));
	QuickSort(E,0,e-1);
	//printMST(E,e);
	j=0;
	for(i=0;i<e;i++)
	{
		if(j==n-1)
			break;
		u=E[i].u;
		v=E[i].v;
		x=find(u);
		y=find(v);
		if(x!=y)
		{
			T[j]=E[i];
			unionbyrank(x,y);
			j++;
		}
	}
	
	printMST(T,n-1);
}

int main()
{
	int i,j,k,n,e,w;
	Edge *E;
	printf("Enter the no. of vertex:");
	scanf("%d",&n);
	printf("\nEnter the no. of edges:");
	scanf("%d",&e);
	
	E=(Edge*)malloc(e*sizeof(Edge));
	
	for(i=1;i<n+1;i++)
	{
		parent[i]=i;
		rank[i]=0;
	}
	
	for(k=0;k<e;k++)
	{
		printf("\nEnter an edge(in form i j w):");
		scanf("%d %d %d",&i,&j,&w);
		E[k].u=i;
		E[k].v=j;
		E[k].w=w;
	}
	
	Kruskal(E,n,e);
}
