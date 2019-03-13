#include<stdio.h>
#include<stdlib.h>
//#include<queue>
//图的矩阵邻接表示
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define VertexType char
#define ArcType int
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];
	ArcType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum,arcnum;
	int kind;
}MGraph; 
int LocateVex(MGraph G,VertexType v){ 
	int i;
	for(i=0;i<G.vexnum;i++)
		if(G.vexs[i]==v) return i;
	return -1;
}
void CreateGraph(MGraph &G){
	int i,j,k;
	char enterc;
	VertexType vi,vj;
	printf("输入顶点数，弧数，种类:");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&G.kind);
	scanf("%c",&enterc);
	printf("输入顶点：");
	for(i=0;i<G.vexnum;i++) scanf("%c",&G.vexs[i]);
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++) G.arcs[i][j]=0;
	scanf("%c",&enterc);
	printf("输入弧:");
	for(k=0;k<G.arcnum;k++){
		printf("%d:",k); 
		scanf("%c%c",&vi,&vj);
		scanf("%c",&enterc);
		i=LocateVex(G,vi);
		j=LocateVex(G,vj);
		G.arcs[i][j]=1;
		if(G.kind==2) G.arcs[j][i]=1;
	}
}
void insertArc(MGraph &G,VertexType vi,VertexType vj){
	int i,j;
	i=LocateVex(G,vi);
	j=LocateVex(G,vj);
	if(i!=-1&&j!=-1){
		G.arcnum++;
		G.arcs[i][j]=1;
		if(G.kind==2) G.arcs[i][j]=1;
	}
}
int FirstAdjVex(MGraph G,int v){
	int j;
	for(j=0;j<G.vexnum;j++)
		if(G.arcs[v][j]!=0) return j;
	return -1;
}
int NextAdjVex(MGraph G,int v,int w){
	int j;
	for(j=w+1;j<G.vexnum;j++)
		if(G.arcs[v][j]!=0) return j;
	return -1;
}
void visite(MGraph G,int v){
	printf("%c ",G.vexs[v]);
}
//深搜 
int visited[MAX_VERTEX_NUM];
void DFS(MGraph G,int v){
	int w;
	visite(G,v);
	visited[v]=true;
	for(w=FirstAdjVex(G,v);w!=-1;w=NextAdjVex(G,v,w))
		if(!visited[w]) DFS(G,w);
}
void DFSTraverse(MGraph G){
	int i,v;
	for(i=0;i<G.vexnum;i++) visited[i]=false;
	for(v=0;v<G.vexnum;v++) 
		if(!visited[v]) DFS(G,v);
}
//广搜
//queue
typedef int ElemType;
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*LinkList;
typedef LinkList Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue;
void CreatQueue_L(LinkQueue &Q){
	Q.front=Q.rear=new LNode;
	Q.front->next=NULL;
}
void DestroyQueue_L(LinkQueue &Q){
	while(Q.front){
		Q.rear=Q.front->next;
		delete Q.front;
		Q.front=Q.rear;
	}
}
void EnQueue_L(LinkQueue &Q,ElemType e){
	LNode *p; 
	p=new LNode;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
bool DeQueue_L(LinkQueue &Q,ElemType &e){
	if(Q.rear==Q.front) return false;
	LNode *p;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	delete p;
	return true;
}
bool EmptyQueue(LinkQueue Q){
	if(Q.front==Q.rear) return true;
	else return false;
}
//
void BFSTraverse(MGraph G){
	LinkQueue Q;
	CreatQueue_L(Q);
	int u,v,w;
	for(v=0;v<G.vexnum;v++) visited[v]=false;
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]){
			visite(G,v);
			visited[v]=true;
			EnQueue_L(Q,v);
			while(!EmptyQueue(Q)){
				DeQueue_L(Q,u);
				w=FirstAdjVex(G,u);
				while(w!=-1){
					if(!visited[w]){
						visite(G,w);
						visited[w]=true;
						EnQueue_L(Q,w);
					}
					w=NextAdjVex(G,u,w);
				}
			}
		}
	}
} 
//网的邻接矩阵表示
void CreateWeb(MGraph &G){
	int i,j,k;
	int num;
	char enterc;
	VertexType vi,vj;
	printf("输入顶点数，弧数，种类:");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&G.kind);
	scanf("%c",&enterc);
	printf("输入顶点：");
	for(i=0;i<G.vexnum;i++) scanf("%c",&G.vexs[i]);
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++) G.arcs[i][j]=INFINITY;
	scanf("%c",&enterc);
	printf("输入弧:");
	for(k=0;k<G.arcnum;k++){
		printf("%d:",k); 
		scanf("%c%c %d",&vi,&vj,&num);
		scanf("%c",&enterc);
		i=LocateVex(G,vi);
		j=LocateVex(G,vj);
		G.arcs[i][j]=num;
		if(G.kind==3) G.arcs[j][i]=num;
	}
}
int MinEdge(int lowcost[],int n){
	int i,k;
	int min=INFINITY;
	for(i=0;i<n;i++){
		if(lowcost[i]!=0&&lowcost[i]<min){
			min=lowcost[i];
			k=i;
		}
	}
	return k;
}
void Prim(MGraph G,int v0,int adjvex[]){
	int lowcost[MAX_VERTEX_NUM];
	int i,j,k;
	for(j=0;j<G.vexnum;j++)
		if(j!=v0){
			lowcost[j]=G.arcs[v0][j];
			adjvex[j]=v0;
		}
	lowcost[v0]=0;
	for(i=0;i<G.vexnum-1;i++){
		k=MinEdge(lowcost,G.vexnum);
		printf("(%c,%c),%d\n",G.vexs[adjvex[k]],G.vexs[k],lowcost[k]);
		lowcost[k]=0;
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[k][j]<lowcost[j]){
				adjvex[j]=k;
				lowcost[j]=G.arcs[k][j];
			}
		}
	}
}
typedef struct{
	int begin;
	int end;
	int power;
}Arc;
void CreatesArc(MGraph G,Arc sArc[]){
	int i,j,k=0;
	for(i=0;i<G.vexnum;i++){
		for(j=i;j<G.vexnum;j++){
			if(G.arcs[i][j]<1000){
				sArc[k].begin=i;
				sArc[k].end=j;
				sArc[k].power=G.arcs[i][j]; 
				//printf("%d	",sArc[k].power);
				k++;
			}
		}
	}
	Arc temp;
	for(i=0;i<G.arcnum-1;i++)
		for(j=i+1;j<G.arcnum;j++)
			if(sArc[i].power>sArc[j].power){
				temp=sArc[i];
				sArc[i]=sArc[j];
				sArc[j]=temp;
			}
	printf("sArc:\n");
	for(i=0;i<G.arcnum;i++)
		printf("(%c,%c) %d\n",G.vexs[sArc[i].begin],G.vexs[sArc[i].end],sArc[i].power);
	printf("\n");
}
void Kruskal(MGraph G){
	Arc *sArc=(Arc*)malloc(sizeof(Arc)*G.arcnum);
	CreatesArc(G,sArc);
	int *index=(int*)malloc(sizeof(int)*G.vexnum);
	int *MSTArcs=(int*)malloc(sizeof(int)*G.vexnum-1);
	int i,j,n;
	int indexBegin,indexEnd;
	for(i=0;i<G.vexnum;i++) index[i]=-1;
	for(i=0;i<G.vexnum-1;i++){
		for(j=0;j<G.arcnum;j++){
			if(!(index[sArc[j].begin]>=0&&index[sArc[j].end]>=0&&index[sArc[j].begin]==index[sArc[j].end])){
				MSTArcs[i]=j;
				if(index[sArc[j].begin]==-1&&index[sArc[j].end]==-1) index[sArc[j].begin]=index[sArc[j].end]=i;
				else if(index[sArc[j].begin]==-1&&index[sArc[j].end]>=0){
					index[sArc[j].begin]=i;
					indexEnd=index[sArc[j].end];
					for(n=0;n<G.vexnum;n++){
						if(index[n]==indexEnd) index[n]=i;
					}
				}
				else if(index[sArc[j].end]==-1&&index[sArc[j].begin]>=0){
					index[sArc[j].end]=i;
					indexBegin=index[sArc[j].begin];
					for(n=0;n<G.vexnum;n++){
						if(index[n]==indexBegin) index[n]=i;
					}
				}
				else{
					indexEnd=index[sArc[j].end];
					indexBegin=index[sArc[j].begin];
					for(n=0;n<G.vexnum;n++)
						if(index[n]==indexBegin||index[n]==indexEnd) index[n]=i;
				}
				break;
			}
		}
	}
	for(i=0;i<G.vexnum-1;i++)
		printf("(%c,%c) %d\n",G.vexs[sArc[MSTArcs[i]].begin],G.vexs[sArc[MSTArcs[i]].end],sArc[MSTArcs[i]].power);
}
void selling(int l){
	int sum=0;
	while(l>10){
		printf("10 ");
		l-=10;
		sum+=30;
	}
	switch(l){
		case 1:printf("1 ");sum+=1;break;
		case 2:printf("2 ");sum+=5;break;
		case 3:printf("3 ");sum+=8;break;
		case 4:printf("2 2 ");sum+=10;break;
		case 5:printf("3 2 ");sum+=13;break;
		case 6:printf("6 ");sum+=17;break;
		case 7:printf("6 1 ");sum+=18;break;
		case 8:printf("6 2 ");sum+=22;break;
		case 9:printf("6 3 ");sum+=25;break;
		case 10:printf("10 ");sum+=30;break;
	}
	printf("sum=%d\n",sum);
}
int main(){
	MGraph G;
	VertexType vi,vj;
	CreateGraph(G);
	DFSTraverse(G);
	printf("\n");
	BFSTraverse(G);
	printf("\n");
	printf("插入边\n");
	scanf("%c %c",&vi,&vj);
	insertArc(G,vi,vj);
	DFSTraverse(G);
	printf("\n");
	BFSTraverse(G);
	printf("prim&Kruskal\n");
	MGraph W;
	CreateWeb(W);
	/*W.arcnum=11;
	W.kind=3;
	W.vexnum=7;
	W.vexs="ABCDEFGeeeeeeeeeeee";
	W.arcs={INFINITY,7,INFINITY,5,INFINITY,INFINITY,INFINITY;7,INFINITY,8,9,7,INFINITY,INFINITY;INFINITY,8,INFINITY,INFINITY,5,INFINITY,INFINITY;5,9,INFINITY,INFINITY,15,6,INFINITY;INFINITY,7,5,15,INFINITY,8,9;INFINITY,INFINITY,INFINITY,6,8,INFINITY,11;INFINITY,INFINITY,INFINITY,INFINITY,9,11,INFINITY;};*/
	BFSTraverse(W);
	int *adjvex=(int*)malloc(sizeof(int)*MAX_VERTEX_NUM);
	printf("Prim:\n");
	Prim(W,0,adjvex);
	printf("Kruskal:\n");
	Kruskal(W); 
	int l;
	scanf("%d",&l);
	selling(l);
}
