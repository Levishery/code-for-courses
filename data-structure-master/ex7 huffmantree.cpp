#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int WeightType;
#define STACK_INIT_SIZE 10
typedef struct{
	WeightType weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef HTNode *HuffTree;
//Õ»²Ù×÷
typedef char ElemType; 
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
void Push(SqStack &S,ElemType e){
	S.elem[++S.top]=e;
}
bool Pop(SqStack &S,ElemType &e){
	if(S.top==-1) return false;
	e=S.elem[S.top--];
	return true; 
} 
// ´´½¨Huffmantree 
void Select(HuffTree HT,int n,int i,int &s1,int &s2){
	int j;
	int s1w,s2w;
	for(j=1;j<=i-1;j++){
		if(HT[j].parent==0) {
			s1w=HT[j].weight;
			s1=j;
			break;
		}
	}
	for(j=1;j<=i-1;j++){
		if(HT[j].parent==0&&HT[j].weight<s1w) {
			s1w=HT[j].weight;
			s1=j;
		}
	}	
	for(j=1;j<=i-1;j++){
		if(HT[j].parent==0&&j!=s1) {
			s2w=HT[j].weight;
			s2=j;
			break;
		}
	}
	for(j=1;j<=i-1;j++){
		if(HT[j].parent==0&&HT[j].weight<s2w&&j!=s1) {
			s2w=HT[j].weight;
			s2=j;
		}
	}
}
void CreateHuffmanTree(HuffTree &HT,WeightType *w,int n){
	int m;
	int s1,s2,i;
	m=n*2-1;
	HT=(HuffTree)malloc(sizeof(HTNode)*(m+1));
	for(i=1;i<=m;i++){
		HT[i].weight= i<=n? w[i-1]:0;
		HT[i].lchild=HT[i].rchild=HT[i].parent=0;
	}
	for(i=n+1;i<=m;i++){
		Select(HT,n,i,s1,s2);
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
		HT[s1].parent=HT[s2].parent=i;
	}
} 
//±àÂë 
void Coding(HuffTree HT,int root,char **HC,SqStack &S){
	char ch;
	if(root!=0){
		if(HT[root].lchild==0){
			Push(S,'\0');
			HC[root]=(char*)malloc(sizeof(char)*STACK_INIT_SIZE);
			strcpy(HC[root],S.elem);
			Pop(S,ch);
		}
		Push(S,'0');
		Coding(HT,HT[root].lchild,HC,S);
		Pop(S,ch);
		Push(S,'1');
		Coding(HT,HT[root].rchild,HC,S);
		Pop(S,ch);
	}
}
void HuffmanCoding(HuffTree HT,char** &HC,int n){
	SqStack S;
	CreatStack_sq(S,STACK_INIT_SIZE);
	HC=(char**)malloc(sizeof(char*)*(n+1));
	Coding(HT,2*n-1,HC,S);
}
void VisitHT(HuffTree HT,int n){
	int j;
	for(j=1;j<=2*n-1;j++) printf("%d ",HT[j].weight);
}
void VisitHC(char **HC,int n){
	int j;
	char *p;
	for(j=1;j<=n;j++){
		p=HC[j];
		while(*p!='\0'){
			printf("%c",*p);p++;
		}
		printf("\n");
	}
}
//·­Òë
void HuffmanDecoding(char **HC,char *s,int n,char *Letter){
		char *p,*pp,*phc;
		int j;
		p=s;
		while(*p!='\0'){
			for(j=1;j<=n;j++){
				pp=p;
				phc=HC[j];
				while(*pp==*phc&&*phc!='\0'){
					pp++;
					phc++;
				}
				if(*phc=='\0'){
					printf("%c",Letter[j-1]);
					p=pp;
					break;
				}
			}
		}
} 
//Çó¶þ²æÊ÷¾µÏñ
//¶þ²æÊ÷»ù´¡ 
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
void Mirror(BiTree T1,BiTree &T2){
		if(T1->lChild){
			T2->rChild=(BiTree)malloc(sizeof(BiTNode));
			T2->rChild->data=T1->lChild->data;
			T2->rChild->lChild=T2->rChild->rChild=NULL;
			Mirror(T1->lChild,T2->rChild);
		} 
		if(T1->rChild){
			T2->lChild=(BiTree)malloc(sizeof(BiTNode));
			T2->lChild->data=T1->rChild->data;
			T2->lChild->lChild=T2->lChild->rChild=NULL;
			Mirror(T1->rChild,T2->lChild);
		} 
}
void MirrorTree(BiTree T1,BiTree &T2){
	T2=(BiTree)malloc(sizeof(BiTNode));
	T2->data=T1->data;
	T2->lChild=T2->rChild=NULL;
	Mirror(T1,T2);
}
//½Úµã×îÔ¶¾àÀë 
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
int longest=0;
void longestd(BiTree T){
	if(T){
		if(depth(T->lChild)+depth(T->rChild)>longest) longest=depth(T->lChild)+depth(T->rChild);
		longestd(T->lChild);
		longestd(T->rChild);
	}
}
/*int num=0;
void leafCoding1(BiTree T,char **LC,SqStack &S){
	char ch;
	if(T!=0){
		if(T->lChild==0&&T->rChild==0){
			Push(S,'\0');
			LC[num]=(char*)malloc(sizeof(char)*STACK_INIT_SIZE);
			strcpy(LC[num],S.elem);
			Pop(S,ch);
			num++;
		}
		Push(S,'0');
		leafCoding1(T->lChild,LC,S);
		Pop(S,ch);
		Push(S,'1');
		leafCoding1(T->rChild,LC,S);
		Pop(S,ch);
	}
}
void leafCoding(BiTree T,char** &LC){
	SqStack S;
	CreatStack_sq(S,STACK_INIT_SIZE);
	LC=(char**)malloc(sizeof(char*)*STACK_INIT_SIZE);
	leafCoding1(T,LC,S);
	*LC[num]='\0';
	num=0;
}*/
void VisitLC(char **LC){
	int j=0;
	char *p;
	while(*LC[j]!='\0'){
		p=LC[j];
		while(*p!='\0'){
			printf("%c",*p);p++;
		}
		printf("\n");
	}
}
int main(){
	printf("**********Huffman±àÂëÓëÒëÂë***********\n");
	int w[]={4,3,7,5,1,6};
	char Letter[]={'A','B','C','D','E','F'};
	int n=6;
	char **HC;
	HuffTree HT;
	CreateHuffmanTree(HT,w,n);
	//VisitHT(HT,n); 
	HuffmanCoding(HT,HC,n);
	VisitHC(HC,n);	char enterc;
	HuffmanDecoding(HC,"110111101",n,Letter);
	printf("**********¾µÏñµÄ¶þ²æÊ÷************\n");
	BiTree T1,T2;

	creatBiTree(T1);
	preOrder(T1);
	printf("\n");
	scanf("%c",&enterc);
	MirrorTree(T1,T2);
	preOrder(T2);
	/*printf("**********½Úµã¾àÀë************\n");
	BiTree T3;
	char **LC;
	creatBiTree(T3);
	preOrder(T3);
	scanf("%c",&enterc);
/*	leafCoding(T3,LC);
	VisitLC(LC);
	longestd(T3);
	printf("%d\n",longest);*/
}
