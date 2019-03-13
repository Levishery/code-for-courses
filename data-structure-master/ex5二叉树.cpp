#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int nodeknum=0;
typedef struct BiTNode{
	char data;
	struct BiTNode *lChild,*rChild;
}BiTNode,*BiTree;
void creatBiTree(BiTree &T){
	char c;
	scanf("%c",&c);
	if(c=='#'){
		T=NULL;
		return;
	}
	else{
		T=(BiTree)malloc(sizeof(BiTNode));
		T->data=c;
		creatBiTree(T->lChild);
		creatBiTree(T->rChild);
	}
}
void preOrder(BiTree T){
	if(!T) return;
	else{
		printf("%c ",T->data);
		preOrder(T->lChild);
		preOrder(T->rChild); 
	}
}
void inOrder(BiTree T){
	if(!T) return;
	else{
		inOrder(T->lChild);
		printf("%c ",T->data);
		inOrder(T->rChild); 
	}
}
void postOrder(BiTree T){
	if(!T) return;
	else{
		postOrder(T->lChild);
		postOrder(T->rChild); 
		printf("%c ",T->data);
	}
}
//队列操作 
typedef BiTree ElemType;
typedef struct LNode{
	ElemType data;
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
bool QueueEmpty_L(LinkQueue Q){
	if(Q.front==Q.rear) return true;
	else return false;
}
//层序遍历 
void levelTraversal(BiTree T){
	LinkQueue Q;
	BiTree p;
	CreatQueue_L(Q);
	if(T) {
	EnQueue_L(Q,T);
	}
	while(!QueueEmpty_L(Q)){
		DeQueue_L(Q,p);//printf("mark2");
		printf("%c ",p->data);
		if(p->lChild) EnQueue_L(Q,p->lChild);
		if(p->rChild) EnQueue_L(Q,p->rChild);
	} 
}
int depth(BiTree T){
	int h1,h2,h;
	if(!T) return 0;
	else{
		depth(T->lChild);
		depth(T->rChild);
		/*if(h1>h2) h=h1;
		else h=h2;*/
		return (h1>h2?h1+1:h2+1); 
	}
}
int countNodes(BiTree T){
	int nl,nr;
	if(!T) return (0);
	else{
		nl=countNodes(T->lChild);
		nr=countNodes(T->rChild);
		return (nl+nr+1);
	} 
} 
//栈操作
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
//非递归遍历 
void preOrder1(BiTree T){
	SqStack S;
	CreatStack_sq(S,MAX); 
	while(!(!T&&StackEmpty_sq(S))){
		while(T){ 
			Push_sq(S,T);
			printf("%c ",T->data);
			T=T->lChild; 
		}  
		if(!StackEmpty_sq(S)){
			Pop_sq(S,T);
			T=T->rChild;
		}
	} 
}
void inOrder1(BiTree T){
	SqStack S;
	CreatStack_sq(S,MAX);
	while(!(!T&&StackEmpty_sq(S))){
		while(T){ 
			Push_sq(S,T);
			T=T->lChild; 
		}  
		if(!StackEmpty_sq(S)){
			Pop_sq(S,T);
			printf("%c ",T->data);
			T=T->rChild;
		}
	} 
}
void postOrder1(BiTree T){
	SqStack S;
	CreatStack_sq(S,MAX);
	BiTree pre=NULL,p;
	Push_sq(S,T);
	while(!StackEmpty_sq(S)){
		Pop_sq(S,p);
		if((p->lChild==NULL&&p->rChild==NULL)||pre!=NULL&&(pre==p->lChild||pre==p->rChild)){
			printf("%c ",p->data);
			pre=p;
		}
		else{
			Push_sq(S,p);
			if(p->rChild!=NULL) Push_sq(S,p->rChild);
			if(p->lChild!=NULL) Push_sq(S,p->lChild);
		}
	}
}
int GetNumBiTree(BiTree T,int k){
	if(k==1&&T!=NULL){
	/*printf("mark");*/return(++nodeknum);
	}
	if(T&&k>1){
		k--;
		GetNumBiTree(T->lChild,k);
		GetNumBiTree(T->rChild,k);
	}
	return(nodeknum);
}
int main(){
	BiTree T;
	int k;
	creatBiTree(T);
	preOrder(T);printf("\n");
	inOrder(T);printf("\n");
	postOrder(T);printf("\n");
	levelTraversal(T);printf("\n");
	printf("树的深度：%d\n树的节点数：%d\n",depth(T),countNodes(T));
	printf("非递归遍历\n");
	preOrder1(T);printf("\n");
	inOrder1(T);printf("\n");
	postOrder1(T);printf("\n");
	printf("输入k：");
	scanf("%d",&k);
	printf("%d",GetNumBiTree(T,k));
}


