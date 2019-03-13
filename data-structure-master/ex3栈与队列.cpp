#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
typedef int ElemType;
typedef char ElemTypec;
typedef struct{
	ElemType *elem;
	int stacksize;
	int top;
}SqStack;
typedef struct{
	ElemTypec *elem;
	int stacksize;
	int top;
}SqStackc;
//
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*LinkList;
typedef LinkList Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue; 
//ջ 
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
void CreatStackc_sq(SqStackc &S,int msize){
	S.elem=new ElemTypec[msize];
	//S.elem=(*ElemType)malloc(msize*sizeof(ElemType));
	S.stacksize=msize;
	S.top=-1;
}
void DestroyStackc_sq(SqStackc &S){
	delete []S.elem;
	//free(S.elem);
	S.top=-1;
	S.stacksize=0;
}
void Pushc_sq(SqStackc &S,ElemTypec e){
	S.elem[++S.top]=e;
}
bool Popc_sq(SqStackc &S,ElemTypec &e){
	if(S.top==-1) return false;
	e=S.elem[S.top--];
	return true; 
}
bool StackEmpty_sq(SqStack &S){
	if(S.top==-1) return true;
	else return false;
}
bool StackEmptyc_sq(SqStackc &S){
	if(S.top==-1) return true;
	else return false;
}
bool StackTraverse_sq(SqStack &S){
	int flag,i;
	printf("����1��ջ����ջ�״�ӡԪ�أ�����2��ջ�׵�ջ����ӡԪ�أ�");
	scanf("%d",&flag);
	if(flag==1) for(i=S.top;i>=0;i--) printf("%d\n",S.elem[i]);
	if(flag==2) for(i=0;i<=S.top;i++) printf("%d\n",S.elem[i]);
}
//���� 
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
//��������
void Knapsack(int w[],int T,int n){
	SqStack S;
	CreatStack_sq(S,STACK_INIT_SIZE);
	int k=0;
	while(!StackEmpty_sq(S)||k!=n){
		while(k!=n&&T>0){
			if(T-w[k]>=0){
				Push_sq(S,k);
				T-=w[k];
			}
			k++;
		}
		if(T==0) StackTraverse_sq(S);
		Pop_sq(S,k);
		T+=w[k];
		k++;
	}
	DestroyStack_sq(S);
}
//��������
bool palin(char *s){
	SqStackc S;
	CreatStackc_sq(S,STACK_INIT_SIZE);
	int n=0,i;
	char *p=s;
	char c;
	while(*p!='\0'){
		p++;
		n++;
	}
	//printf("%d",n);
	p=s;
	for(i=0;i<n/2;i++){
		Pushc_sq(S,*p);
		p++;
		}
	if(n%2==1) p++;
	for(i=0;i<n/2;i++){
		Popc_sq(S,c);
		//printf("%c",c);
		//printf("%c",*p);
		if(c!=*p) {
		Pushc_sq(S,c); 
		break;
		} 
		p++;
	}
	if(StackEmptyc_sq(S)) return true;
	else return false;
} 
int main(){
	SqStack S;
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int w[6]={2,8,6,5,1,4};
	int i,T=11,n=6,flag;
	char ch[10];
	ElemType c,d,f;
	printf("*****************����ջ***************\n");
	CreatStack_sq(S,STACK_INIT_SIZE);
	printf("����ջ\n");
	if(StackEmpty_sq(S)) printf("ջΪ��\n");
	else printf("ջ�ǿ�\n");
	printf("��ʼ��ջ\n");
	for(i=0;i<=9;i++) Push_sq(S,a[i]);
	StackTraverse_sq(S);
	printf("�޸�ջ\n");
	Pop_sq(S,c);
	Pop_sq(S,d);
	Push_sq(S,c+d);
	StackTraverse_sq(S);
	StackTraverse_sq(S);
	printf("����ջ\n");
	DestroyStack_sq(S); 
	printf("****************���Զ���***************\n");
	LinkQueue Q;
	printf("��������\n");
	CreatQueue_L(Q);
	printf("��ʼ������\n");
	for(i=0;i<=9;i++) EnQueue_L(Q,a[i]);
	printf("�����в���ӡ\n");
	for(i=0;i<=9;i++){
		DeQueue_L(Q,f);
		printf("%d\n",f);
	}
	printf("���ٶ���\n");
	printf("*****************��������****************\n");
	Knapsack(w,T,n);
	printf("*****************�����ж�****************\n");
	scanf("%s",&ch);
	if(palin(ch)) printf("�ǻ���\n");
	else printf("����\n");
	scanf("%s",&ch);
	if(palin(ch)) printf("�ǻ���\n");
	else printf("����\n");
}
