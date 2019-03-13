#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100 
typedef int keytype;
typedef int infotype;
typedef struct{
	keytype key;
	infotype otherinfo;
}RcdType;
typedef struct{
	RcdType r[MAXSIZE+1];
	int len;
}SqTable; 
//»ù±¾²Ù×÷ 
void InitL(SqTable &L){
	L.len=6;
	L.r[0].key=L.r[0].otherinfo=-1;
	L.r[1].key=L.r[1].otherinfo=6;L.r[2].key=L.r[2].otherinfo=7;L.r[3].key=L.r[3].otherinfo=5;L.r[4].key=L.r[4].otherinfo=2;L.r[5].key=L.r[5].otherinfo=5;L.r[6].key=L.r[6].otherinfo=8;
}
void printL(SqTable L){
	int i;
	for(i=1;i<=L.len;i++) printf("%d ",L.r[i].otherinfo);
	printf("\n");
}//
//Ï£¶ûÅÅÐò
void swap(RcdType &a,RcdType &b){
	RcdType temp;
	temp.key=a.key;
	a.key=b.key;
	b.key=temp.key;
	temp.otherinfo=a.otherinfo;
	a.otherinfo=b.otherinfo;
	b.otherinfo=temp.otherinfo;
}
void InsSort2(RcdType A[],int n,int incr){
	int i,j;
	for(i=incr;i<=n;i+=incr)
		for(j=i;(j>=incr)&&(A[j].key<A[j-incr].key);j-=incr)
			swap(A[j],A[j-incr]);
}
void ShlSort(SqTable &L){
	int i,j,n;
	n=L.len;
	for(i=n/2;i>2;i/=2){
		//printL(L);
		for(j=1;j<=i;j++)
			InsSort2(&L.r[j],n+1-j,i);
	}
//	printL(L);
	InsSort2(&L.r[1],n,1);
} //

// ¿ìËÙÅÅÐò
int FindPivot(SqTable L,int i,int j){
	return (i+j)/2;
} 
int partition(SqTable &L,int i,int r,keytype pivot){
	int l=i-1;
	do{
		while(L.r[++l].key<pivot);
		while(r>=i&&L.r[--r].key>pivot);
		swap(L.r[l],L.r[r]);//printL(L);
	}while(l<r);//
	swap(L.r[l],L.r[r]);
	return l;
}
void QuiSort(SqTable &L,int i,int j){
	int k;
	int pivotIndex=FindPivot(L,i,j);
	swap(L.r[pivotIndex],L.r[j]);//printL(L);
	k=partition(L,i,j,L.r[j].key);
	swap(L.r[k],L.r[j]);
	//printL(L);
	if((k-i)>1) QuiSort(L,i,k-1);
	if((j-k)>1) QuiSort(L,k+1,j);
}
//¶ÑÅÅÐò
typedef SqTable HeapList;
void HeapAdjust(HeapList &L,int s,int t){
	RcdType w;
	int i;
	w=L.r[s];
	for(i=2*s;i<=t;i*=2){
		if(i<t) i=(L.r[i].key>L.r[i+1].key)? i:i+1;
		 if(w.key>=L.r[i].key) break;
		 L.r[s]=L.r[i];
		 s=i; 
	}
	L.r[s]=w;
} 
void HeapSort(HeapList &L){
	int i;
	for(i=L.len/2;i>=1;i--) HeapAdjust(L,i,L.len);
	for(i=L.len;i>1;i--){
		swap(L.r[1],L.r[i]);
		HeapAdjust(L,1,i-1);
	}
}//
//¹é²¢ÅÅÐò 
void Merge(RcdType Rs[],RcdType Rt[],int s,int m,int t){
	int i,j,k;
	for(i=s,j=m+1,k=i;i<=m&&j<=t;k++){
		if(Rs[i].key<=Rs[j].key) Rt[k]=Rs[i++];
		else Rt[k]=Rs[j++]; 
	}
	for(;i<=m;) Rt[k++]=Rs[i++];
	for(;j<=t;) Rt[k++]=Rs[j++]; 
}
void MSortPass(RcdType Rs[],RcdType Rt[],int s,int t){
	if(s==t){
		Rt[s]=Rs[s];return;
	}
	int m;
	RcdType *Rtmp;
	Rtmp=(RcdType*)malloc(MAXSIZE*sizeof(RcdType));
	m=(s+t)/2;
	MSortPass(Rs,Rtmp,s,m);
	MSortPass(Rs,Rtmp,m+1,t);
	Merge(Rtmp,Rt,s,m,t);
}
void MergeSort(SqTable &L){
	MSortPass(L.r,L.r,1,L.len);
}
int main(){
	SqTable L;
	printf("Ï£¶ûÅÅÐò£º\n");
	InitL(L);
	ShlSort(L);
	printL(L);
	printf("¿ìËÙÅÅÐò£º\n");
	InitL(L);
	QuiSort(L,1,L.len);
	printL(L);
	printf("¶ÑÅÅÐò:\n");
	InitL(L);
	HeapSort(L);
	printL(L);
	printf("¹é²¢ÅÅÐò:\n");
	InitL(L);
	MergeSort(L);
	printL(L);
}
