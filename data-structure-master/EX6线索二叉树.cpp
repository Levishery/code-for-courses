#include<stdio.h>
#include<stdlib.h>
#define TElemType char
#define MAX 100
typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lChild,*rChild;
	unsigned char ltag,rtag;
}BiThrNode,*BiThrTree; 
//建立二叉树 
void creatBiTree(BiThrTree &T){
	char c;
	scanf("%c",&c);
	if(c=='#'){
		T=NULL;
		return;
	}
	else{
		T=(BiThrTree)malloc(sizeof(BiThrNode));
		T->data=c;
		T->ltag=0;
		T->rtag=0; 
		creatBiTree(T->lChild);
		creatBiTree(T->rChild);
	}
}
//中序线索化 
BiThrTree pre=NULL; 
void InThreading(BiThrTree &T){
	if(T){
		InThreading(T->lChild);
		if(!T->lChild){
			T->lChild=pre;
			T->ltag=1;
		}
		if(pre&&!pre->rChild){
			pre->rChild=T;
			pre->rtag=1;
		}
		pre=T;
		InThreading(T->rChild);
	}
}
//寻找后继
BiThrTree GetNext(BiThrTree p){
	if(p->rtag==1) return p->rChild;
	else{
		BiThrTree q;
		q=p->rChild;
		while(q->ltag==0) q=q->lChild;
		return q;
	}
}
//利用线索遍历 
void InOrder(BiThrTree T){
	BiThrTree p=T;
	while(p->ltag==0) p=p->lChild;
	do{
		printf("%c",p->data);
		p=GetNext(p);
	}while(p!=NULL);
}
//节点是否在树中
bool isflag=false;
bool IsInTree1(BiThrTree T,BiThrNode *R){
	if(isflag==true) return true;
	if(R->data==T->data) {isflag=true;return true;}
	else{
		if(T->ltag==0&&T->lChild) IsInTree1(T->lChild,R);
		if(T->rtag==0&&T->rChild) IsInTree1(T->rChild,R);
	}
	return isflag;
}
bool IsInTree(BiThrTree T,BiThrNode *R){
	bool isflag0;
	isflag0=IsInTree1(T,R);
	isflag=false;
	return isflag0;
}
/*BiThrTree GetLastParent(BiThrTree T,BiThrNode *M,BiThrNode *N){
	BiThrTree p=T;
	while(p->ltag==0) p=p->lChild;
	while(p){
		//printf("%c",p->data);printf("%d%d",IsInTree(p,M),IsInTree(p,N));
		if(IsInTree(p,M)==true&&IsInTree(p,N)==true) {
		//printf("%s","break");
		return p;
		}
		p=postGetNext(p);
	}
	return p; 
}
//栈操作
typedef BiThrTree ElemType;
typedef struct{
	ElemType *elem;
	int stacksize;
	int top;
}SqStack;
void CreatStack_sq(SqStack &S,int msize){
	S.elem=new ElemType[msize];
	//S.elem=(*ElemType)malloc(msize*sizeof(ElemType));
	S.stacksize=msize;
	S.top=-1;
}
void DestroyStack_sq(SqStack &S){
	delete []S.elem;
	//free(S.elem);
	S.top=-1;
	S.stacksize=0;
}
void Push_sq(SqStack &S,ElemType e){
	S.elem[++S.top]=e;
}
bool Pop_sq(SqStack &S,ElemType &e){
	if(S.top==-1) return false;
	e=S.elem[S.top--];
	return true; 
} 
bool StackEmpty_sq(SqStack &S){
	if(S.top==-1) return true;
	else return false;
}
BiThrTree GetLastParent(BiThrTree T,BiThrNode *M,BiThrNode *N){
	SqStack S;
	CreatStack_sq(S,MAX);
	BiThrTree pre=NULL,p;
	Push_sq(S,T);
	while(!StackEmpty_sq(S)){
		Pop_sq(S,p);
		if((p->ltag==1&&p->rtag==1)||pre!=NULL&&((p->ltag==0&&pre==p->lChild)||(p->rtag==0&&pre==p->rChild))){
			if(IsInTree(p,M)==true&&IsInTree(p,N)==true) {
				//printf("%s","break");
				return p;
				pre=p;
			}
		}
		else{
			Push_sq(S,p);
			if(p->rtag==0&&p->rChild!=NULL) Push_sq(S,p->rChild);
			if(p->ltag==0&&p->lChild!=NULL) Push_sq(S,p->lChild);
		}
	}
}*/
BiThrTree GetLastParent(BiThrTree T,BiThrNode *M,BiThrNode *N){
	if((T->ltag==0&&IsInTree(T->lChild,M)==true)&&(T->rtag==0&&IsInTree(T->rChild,N)==true)){
		return T;
	}
	if((T->ltag==0&&IsInTree(T->lChild,N)==true)&&(T->rtag==0&&IsInTree(T->rChild,M)==true)){
		return T;
	}
	if((T->ltag==0&&IsInTree(T->lChild,M)==true)&&(T->ltag==0&&IsInTree(T->lChild,N)==true)){
		GetLastParent(T->lChild,M,N);
	}
	if((T->rtag==0&&IsInTree(T->rChild,M)==true)&&(T->rtag==0&&IsInTree(T->rChild,N)==true)){
		GetLastParent(T->rChild,M,N);
	}
}
int main(){
	BiThrTree T;
	creatBiTree(T);
	char c;
	scanf("%c",&c);
	InThreading(T);
	//printf("%c",pre->data);
	pre->rtag=1;//最后一个遍历的节点右tag没有置1！ 
	//printf("%d",pre->rtag);
	printf("中序遍历线索树：");
	InOrder(T);
	printf("\n");
	BiThrNode *R;
	char rdata;
	char s1[]="在树中";
	char s2[]="不在树中"; 
	R=(BiThrTree)malloc(sizeof(BiThrNode));
	R->lChild=R->rChild=NULL;
	R->ltag=R->rtag=0;
	printf("输入要查找的节点data:");
	scanf("%c",&rdata);
	scanf("%c",&c);
	R->data=rdata;
	printf("%s\n",IsInTree(T,R)?s1:s2);
	BiThrNode *M,*N;
	char mdata,ndata;
	M=(BiThrTree)malloc(sizeof(BiThrNode));
	N=(BiThrTree)malloc(sizeof(BiThrNode));
	M->lChild=N->rChild=N->lChild=M->rChild=NULL;
	M->ltag=M->rtag=N->ltag=N->rtag=0;
	printf("输入要查找的两个节点data:");
	scanf("%c%c",&mdata,&ndata);
	M->data=mdata;N->data=ndata;
	//printf("%c %c",M->data,N->data);
	if(GetLastParent(T,M,N)==NULL) printf("没有公共双亲\n");
	else{
		printf("%c",GetLastParent(T,M,N)->data);
	}
}

