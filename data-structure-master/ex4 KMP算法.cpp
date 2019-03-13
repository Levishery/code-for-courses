#include<stdio.h>
#define MAX_LEN 255 
typedef char
SString[MAX_LEN+1];
#define MAX_SIZE 1000
//四皇后 
#define QNUM 4
int result[QNUM];
int diag1[2*QNUM-1],diag2[2*QNUM-1];
int line[QNUM];
void mark(int i,int j,int flag){
	diag1[i+j]=diag2[i-j+7]=line[j]=flag;
}
int canput(int i,int j){
	return(line[j]==0&&diag1[i+j]==0&&diag2[i-j+7]==0);
}
void printresult(int result[]){
	int i;
	for(i=0;i<QNUM;i++)
	printf("%d\n",result[i]);
}
void disqueen(int i){
	int j;
	for(j=0;j<QNUM;j++){
		if(canput(i,j)) {
			mark(i,j,1);
			result[i]=j;
			if(i==QNUM-1) {
				printresult(result);printf("\n");
			}
			else disqueen(i+1);
			mark(i,j,0);//回溯 
		}
	}
}
int StrLength(SString T){
	int i=0;
	while(T[i]!='\0'){
		i++;
	}
	//printf("%d	m	",i);
	return (i);
}
//KMP
void GetNext(SString p,int next[]){
	int j,k;
	j=0;k=-1;next[0]=-1;
	//printf("%d\n",StrLength(p));
	while(j<=StrLength(p)-1){
		//printf("mark2\n");
		if(k==-1||p[j]==p[k]){
			j++;k++;
			if(p[j]!=p[k]) next[j]=k;
			else next[j]=next[k];
			//printf("%d	",next[j]);
		}
		else k=next[k];
	}
}
int PrintNext(int next[],int len){
	int i;
	for(i=0;i<len;i++) printf("%d	",next[i]);
}
int Find_KMP(SString S,SString p,int start){

	int i=start,j=0;
	int next[255];//printf("mark\n");
	GetNext(p,next);
	if(start<0||start>StrLength(S)-StrLength(p)){
	//printf("非法start值\n");
	PrintNext(next,StrLength(p));printf("\n");
	return -1;
	}
	//PrintNext(next,StrLength(p));
	while(i<StrLength(S)&&j<StrLength(p))
		if(j==-1||S[i]==p[j]){
			i++;j++;
		}
		else j=next[j];
		if(j==StrLength(p)) return(i-j);
		return -1;
}
//串操作
void StrAssign(SString &T,char s[]){
	char *p;
	int i=0;
	p=s;
	while(*p!='\0'){
		T[i]=*p;
		//printf("%c",T[i]);
		p++;i++;
	}
	T[i]='\0';
} 
void StrCopy(SString &T,SString s){
	int i=0,j=0;
	while(s[j]!='\0'){
		T[i]=s[j];
		i++;j++;
	}
	T[i]='\0';
} 

int StrCompare(SString S,SString T){
	while(*T!='\0'&&*S!='\0'){
		if(*T==*S){
			T++;S++;
		} 
		else return(*S-*T);
	}
	if(*T=='\0'&&*S=='\0') return 0;
	if(*T=='\0') return -1;
	if(*S=='\0') return 1;
}
void StrConcat(SString &T,SString s1,SString s2){
	char *p,*q;
	p=s1;q=T;
	while(*p!='\0'){
		*q=*p;p++;q++;
	}
	p=s2;
	while(*p!='\0'){
		*q=*p;p++;q++;
	}
	*q='\0';
}
int Substring(SString &Sub,SString s,int pos,int len){
	if(pos<0||pos>StrLength(s)-1||len<=0||len>StrLength(s)-pos){
	printf("输入非法\n");
	return -1;
	}
	char *p=s,*q=Sub;
	int i;
	for(i=0;i<pos;i++) p++;
	for(i=0;i<len;i++){
		*q=*p;
		q++;
		p++;
	}
}
void Replace2(SString &S,SString v,int pos,int len){
	char *p=S;
	char *tail,*start;
	SString result0,result;
	int i;
	for(i=0;i<pos;i++) p++;
	*p='\0';
	for(i=0;i<len;i++) p++;
	tail=p;

	StrConcat(result0,S,v);
	StrConcat(result,result0,tail);
	StrCopy(S,result);
}
void Replace(SString &S,SString t,SString v){
	int p=0;
	int lent=StrLength(t);
	int lenv=StrLength(v);
	while(1){
		p=Find_KMP(S,t,p+lenv);
		if(p==-1) break;
		Replace2(S,v,p,lent);
	}
}
//数字分割
/*void divid(int n){
	if(n==1) return;
	int i;
	for(i=n-1;i>=1;i--){
		divid(i);
		printf("%d+",i);
	}
	printf("\n");
}*/
int main(){
	printf("*************四皇后*************\n");
	disqueen(0);
	printf("*************KMP*****************\n");
	SString S1,S2,S3,P1,P2,P3,V;
	printf("1:	abcabcabcd	abcabcd\n");
	char s1[]="abcabcabcd"; 
	char p1[]="abcabcd";
	char v[]="AAA";
	StrAssign(S1,s1);
	StrAssign(P1,p1);
	StrAssign(V,v);
	//printf("赋值成功\n");
	//SString s1="abcabcabcd";
	//SString p1="abcabcd";
	//SString v="AAA";
	int result;
	result=Find_KMP(S1,P1,0);
	//printf("result=%d\n",result);
	Replace(S1,P1,V);
	printf("替换后S=%s\n",S1);
	printf("2:	abcdababcabcdabcabcabcd	abcabcd\n");
	SString s2="abcdababcabcdabcabcabcd";
	SString p2="abcabcd";
	result=Find_KMP(s2,p2,0);
	//printf("result=%d\n",result);
	Replace(s2,p2,v);
	printf("替换后s=%s\n",s2);
	printf("3:	cocaocoaoc	coaoc\n");
	SString s3="cocaocoaoc";
	SString p3="coaoc";
	result=Find_KMP(s3,p3,0);
	//printf("result=%d\n",result);
	Replace(s3,p3,v);
	printf("替换后s=%s\n",s3);
	/*printf("***************分割数**************\n");
	divid(6); */
	/*printf("***************串操作***************\n)；
	SString s4="abcdefg";
	SString s5="abcdefh";
	SString s6;
	if(StrCompare(s4,s5)) printf("s4>s5") */
} 
