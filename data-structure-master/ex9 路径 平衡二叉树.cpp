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
void Dijkstra(MGraph G,int v0,int D[MAX_VERTEX_NUM],int P[][MAX_VERTEX_NUM]){
	int i,j,k,w;
	int min;
	int S[MAX_VERTEX_NUM]={0};
	for(i=0;i<G.vexnum;i++){
		D[i]=G.arcs[v0][i];
		if(D[i]!=INFINITY){
			P[i][0]=v0;P[i][1]=i;P[i][2]=-1;
		}
	}
	S[v0]=1;
	D[v0]=0;
	P[v0][0]=v0;P[v0][1]=-1;
	for(i=1;i<G.vexnum;i++){
		min=INFINITY;
		for(j=0;j<G.vexnum;j++)
			if(!S[j]&&D[j]<min){
				min=D[j];
				k=j;
			}
		S[k]=1;
		for(j=0;j<G.vexnum;j++)
			if(!S[j]&&G.arcs[k][j]!=INFINITY&&D[k]+G.arcs[k][j]<D[j]){
				D[j]=D[k]+G.arcs[k][j];
				for(w=0;P[k][w]!=-1;w++) P[j][w]=P[k][w];
				P[j][w]=j;P[j][w+1]=-1;
			}
	}
}
void maxDijkstra(MGraph G,int v0,int D[MAX_VERTEX_NUM],int P[][MAX_VERTEX_NUM]){
	int i,j,k,w;
	int max;
	int S[MAX_VERTEX_NUM]={0};
	for(i=0;i<G.vexnum;i++){
		D[i]=G.arcs[v0][i];
		if(D[i]!=INFINITY){
			P[i][0]=v0;P[i][1]=i;P[i][2]=-1;
		}
	}
	S[v0]=1;
	D[v0]=0;
	P[v0][0]=v0;P[v0][1]=-1;
	for(i=1;i<G.vexnum;i++){
		max=0;
		for(j=0;j<G.vexnum;j++)
			if(!S[j]&&D[j]>max&&D[j]<1000){
				max=D[j];
				k=j;
			}
		S[k]=1;
		for(j=0;j<G.vexnum;j++)
			if(D[j]==INFINITY){
				D[j]=D[k]+G.arcs[k][j];
				for(w=0;P[k][w]!=-1;w++) P[j][w]=P[k][w];
				P[j][w]=j;P[j][w+1]=-1;
			}
			else if(!S[j]&&G.arcs[k][j]!=INFINITY&&D[k]+G.arcs[k][j]>D[j]){
				D[j]=D[k]+G.arcs[k][j];
				for(w=0;P[k][w]!=-1;w++) P[j][w]=P[k][w];
				P[j][w]=j;P[j][w+1]=-1;
			}
	}
}
//二叉检索树
typedef struct BiTNode{
	int data;
	struct BiTNode *lChild,*rChild;
}BiTNode,*BiTree;
void creatBiTree(BiTree &T){
	int n;
	scanf("%d",&n);
	if(n==0){
		T=NULL;
		return;
	}
	else{
		T=(BiTree)malloc(sizeof(BiTNode));
		T->data=n;
		creatBiTree(T->lChild);
		creatBiTree(T->rChild);
	}
} 
void preOrder(BiTree T){
	if(!T) return;
	else{
		printf("%d ",T->data);
		preOrder(T->lChild);
		preOrder(T->rChild); 
	}
}
int BinearySearchTreeMax(BiTree T){
	BiTree p;
	p=T;
	while(p->rChild!=NULL){
		p=p->rChild;
	}
	return p->data;
} 
int BinearySearchTreeMin(BiTree T){
	BiTree p;
	p=T;
	while(p->lChild!=NULL){
		p=p->lChild;
	}
	return p->data;
} 
/*void insert(BiTree &T,int e){
	BiTree p;
	p=T;
	while(p!=NULL){
		if(p->data>e) p=p->lChild;
		else p=p->rChild;
	}
	p=(BiTree)malloc(sizeof(BiTNode));
	p->data=e;
	p->lChild=NULL;
	p->rChild=NULL;
}*/
bool BinSrTree(BiTree BT,int kval,BiTree &p,BiTree &f){
	p=BT;
	while(p){
		if(p->data==kval) return true;
		else{
			f=p;
			if(p->data>kval) p=p->lChild;
			else p=p->rChild;
		}
	}
	return false;
}
bool BinSrTree_Ins(BiTree &BT,int kval){
	BiTree f,t,p;
	f=NULL;
	if(BinSrTree(BT,kval,p,f)) return false;
	else{
		t=new BiTNode;
		t->data=kval;
		t->lChild=t->rChild=NULL;
		if(!f) BT=t;
		else if(kval<f->data) f->lChild=t;
			else f->rChild=t;
		return true;
	}
}
bool BinSrTree_Del(BiTree &BT,int kval){
	BiTree f=NULL;
	BiTree p,q,t;
	if(!BinSrTree(BT,kval,p,f)) return false;
	else{
		if(p->lChild&&p->rChild){
			q=p;
			t=p->rChild;
			while(t->lChild){
				q=t;t-t->lChild;
			}
			p->data=t->data;
			if(q!=p) q->lChild=t->rChild;
			else q->rChild=t->rChild;
			free(t);
		}
		else{
			q=p;
			if(!p->rChild) p=p->lChild;
			else p=p->rChild;
			if(!f) BT=p;
			else{
				if(q==f->lChild) f->lChild=p;
				else f->rChild=p;
			} 
			free(q);
		}
	}
}
int main(){
	MGraph G;
	CreateWeb(G);
	int D1[MAX_VERTEX_NUM],P1[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int D2[MAX_VERTEX_NUM],P2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int v0=0;
	int i,j;
	Dijkstra(G,v0,D1,P1);
	maxDijkstra(G,v0,D2,P2);
	for(i=0;i<G.vexnum;i++){
		printf("%c->%c:%d ",G.vexs[v0],G.vexs[i],D1[i]);
		for(j=0;P1[i][j]!=-1;j++) printf("%d ",P1[i][j]);
	}
	printf("\n");
	for(i=0;i<G.vexnum;i++){
		printf("%c->%c:%d ",G.vexs[v0],G.vexs[i],D2[i]);
		for(j=0;P2[i][j]!=-1;j++) printf("%d ",P2[i][j]);
	}
	printf("\n");
	printf("********检索二叉树**********\n");
	BiTree T;
	int kvali,kvald;
	creatBiTree(T);
	preOrder(T);
	printf("最大：%d	最小：%d\n",BinearySearchTreeMax(T),BinearySearchTreeMin(T));
	printf("插入：");scanf("%d",&kvali); 
	BinSrTree_Ins(T,kvali);
	preOrder(T);
	printf("\n");
	printf("删除：");scanf("%d",&kvald); 
	BinSrTree_Del(T,kvald);
	preOrder(T);
}
