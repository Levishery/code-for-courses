//
//  main.cpp
//  red_black_tree
//
//  Created by Jane Chen on 2019/4/20.
//  Copyright © 2019年 Jane Chen. All rights reserved.
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <fstream>
using namespace std;

//数据结构
typedef struct rbTNode{
    int cid;
    string cname;
    int max;
    int ctime1; //左区间，12点10分：1210
    int ctime2;
    bool color; //0 = black ，1 = red
    struct rbTNode *lChild,*rChild,*p;
}rbTNode,*rbTree;

//创建节点
void IniNIL(rbTNode *NIL){
    string cname_ = "NIL";
    NIL->cname = cname_;
    NIL->max = 0;
    NIL->ctime1 = 0;
    NIL->ctime2 = 0;
    NIL->cid = 0;
    NIL->color = 0;
    NIL->lChild = NULL;
    NIL->rChild = NULL;
    NIL->p = NULL;
}
void IniEmp(rbTNode *NIL){
    NIL->max = 0;
    NIL->ctime1 = 0;
    NIL->ctime2 = 0;
    NIL->cid = 9999;
    NIL->color = 0;
    NIL->lChild = NULL;
    NIL->rChild = NULL;
    NIL->p = NULL;
}

int pow(int x, int y){
    int i;
    int r;
    r = 1;
    for(i=0;i<y;i++){
        r*= x;
    }
    return r;
}

rbTNode* Create_Node(){
    rbTNode *z = (rbTree)malloc(sizeof(rbTNode));
    int cid_;
    int ctime1_,ctime2_;
    string cname1;
    printf("cid:");
    scanf("%d",&cid_);
    z->cid=cid_;
    printf("cname:");
    cin>>cname1;
    z->cname = cname1;
    printf("time:");
    scanf("%d %d",&ctime1_,&ctime2_);
    z->ctime1 = ctime1_;
    z->ctime2 = ctime2_;
    z->max = z->ctime2;
    return z;
}

//层序遍历
typedef rbTree ElemType;
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
int depth(rbTree T){
    int h1,h2;
    if(!T) return 0;
    else{
        h1 = depth(T->lChild);
        h2 = depth(T->rChild);
        /*if(h1>h2) h=h1;
         else h=h2;*/
        return (h1>h2?h1+1:h2+1);
    }
}
void levelTraversal(rbTree T){
    LinkQueue Q;
    int dep = depth(T);
    //printf("%d",dep);
    rbTree p;
    rbTNode *Emp = (rbTree)malloc(sizeof(rbTNode));
    IniEmp(Emp);
    CreatQueue_L(Q);
    if(T) {
        EnQueue_L(Q,T);
    }
    int num = 0;
    int d = 0;
    int i;
    while(!QueueEmpty_L(Q)){
        if (d>dep)
            break;
        for(i=d;i<=dep;i++)
            printf("    ");
        DeQueue_L(Q,p);
        if(p->cid == 9999){
            printf("    ");
        }
        else{
            std::cout << p->cname;  ///033[41;32m字体背景是红色，字是绿色/033[0m
            if(p->color == 1)
            printf("(%d-%d)" ,p->ctime1,p->ctime2);
            else printf("*(%d-%d)" ,p->ctime1,p->ctime2);
        }
        num++;
        if ((num+1)%(pow(2,d)) == 0){
            printf("\n");
            d++;
        }
        if(p->lChild) EnQueue_L(Q,p->lChild);
        else EnQueue_L(Q, Emp);
        if(p->rChild) EnQueue_L(Q,p->rChild);
        else EnQueue_L(Q, Emp);
    }
}
//层序遍历

//建树，只有根节点
int Max(int a, int b, int c);
void creatrbTree(rbTree &T, rbTNode *NIL){
    int cid_;
    int ctime1_,ctime2_;
    printf("cid:");
    scanf("%d",&cid_);
    T=(rbTree)malloc(sizeof(rbTNode));
    T->cid=cid_;
    printf("cname:");
    cin>>T->cname;
    printf("time:");
    scanf("%d %d",&ctime1_,&ctime2_);
    T->ctime1 = ctime1_;
    T->ctime2 = ctime2_;
    T->color = 0;
    T->lChild = NIL;
    T->rChild = NIL;
    T->max = ctime2_;
    T->p = NIL;
}
void creatrbTree2(rbTree &T, rbTNode *NIL){ //  有三个节点的树
    rbTNode *R=(rbTree)malloc(sizeof(rbTNode));
    T = R;
    R->cid=1;
    R->cname = "math";
    R->ctime1 = 11;
    R->ctime2 = 12;
    R->color = 0;
    
    rbTNode *L=(rbTree)malloc(sizeof(rbTNode));
    rbTNode *RR=(rbTree)malloc(sizeof(rbTNode));
    R->lChild = L;
    R->rChild = RR;
    
    L->cid=2;
    L->cname = "py";
    L->ctime1 = 5;
    L->ctime2 = 6;
    L->color = 0;
    L->max = 6;
    L->lChild = NIL;
    L->rChild = NIL;
    L->p = R;
    
    RR->cid=3;
    RR->cname = "ch";
    RR->ctime1 = 17;
    RR->ctime2 = 18;
    RR->color = 0;
    RR->max = 8;
    RR->lChild = NIL;
    RR->rChild = NIL;
    RR->p = R;
    
    R->max = 12;
    T->p = NIL;
}
//建树

//旋转
void Left_Rotate(rbTree &T, rbTNode *x){
    rbTNode *y = x->rChild;
    x->rChild = y->lChild;
    if (y->lChild->cname != "NIL")
        y->lChild->p = x;
    y->p = x->p;
    if (x->p->cname == "NIL")
        T = y;
    else{
        if (x ==x->p->lChild)
            x->p->lChild = y;
        else x->p->rChild = y;
    }
    y->lChild = x;
    x->p = y;
    x->max = Max(x->ctime2, x->lChild->max, x->rChild->max);
    y->max = Max(y->ctime2, y->lChild->max, y->rChild->max);
}
void Right_Rotate(rbTree &T, rbTNode *y){
    rbTNode *x = y->lChild;
    y->lChild = x->rChild;
    if (x->rChild->cname != "NIL")
        x->rChild->p = y;
    x->p = y->p;
    if (y->p->cname == "NIL")
        T = x;
    else{
        if (y ==y->p->lChild)
            y->p->lChild = x;
        else y->p->rChild = x;
    }
    x->rChild = y;
    y->p = x;
    y->max = Max(y->ctime2, y->lChild->max, y->rChild->max);
    x->max = Max(x->ctime2, x->lChild->max, x->rChild->max);
}
//旋转

//插入
void RB_Insert_Fix(rbTree &T, rbTNode *z);
void RB_Insert(rbTree &T, rbTNode *z){
    rbTNode *y = T->p;
    rbTNode *x = T;
    while(x->cname != "NIL"){
        y = x;
        if(z->ctime1 < x->ctime1)
            x = x->lChild;
        else x = x->rChild;
    }
    z->p = y;
    if(y->cname == "NIL")
        T = z;
    else if (z->ctime1 < y->ctime1)
        y->lChild = z;
    else    y->rChild = z;
    z->lChild = T->p;
    z->rChild = T->p;
    z->color = 1;
    RB_Insert_Fix(T,z);
}
void RB_Insert_Fix(rbTree &T, rbTNode *z){
    while(z->p->color == 1){
        if(z->p == z->p->p->lChild){    //  z的父亲是左孩子
            rbTNode *y = z->p->p->rChild;
            if(y->color == 1){      //  情况 1
                z->p->color = 0;
                y->color = 0;
                z->p->p->color = 1;
                z = z->p->p;
            }
            else{
                if (z == z->p->rChild){    //  情况2左旋得情况3
                    z = z->p;
                    Left_Rotate(T, z);
                }
            z->p->color = 0;    //  情况3
            z->p->p->color = 1;
            Right_Rotate(T, z->p->p);
            }
        }
        else{   //  对称
            rbTNode *y = z->p->p->lChild;
            if(y->color == 1){      //  情况 1
                z->p->color = 0;
                y->color = 0;
                z->p->p->color = 1;
                z = z->p->p;
            }
            else{
                if (z == z->p->lChild){    //  情况2左旋得情况3
                    z = z->p;
                    Right_Rotate(T, z);
                }
            z->p->color = 0;    //  情况3
            z->p->p->color = 1;
            Left_Rotate(T, z->p->p);
            }
        }
    }
    T->color = 0;
}
//插入

//删除
rbTNode *SortbyID(rbTree T, int id){
    LinkQueue Q;
    rbTree p;
    CreatQueue_L(Q);
    if(T) {
        EnQueue_L(Q,T);
    }
    while(!QueueEmpty_L(Q)){
        DeQueue_L(Q,p);
        if(p->cid == id) return p;
        if(p->lChild) EnQueue_L(Q,p->lChild);
        if(p->rChild) EnQueue_L(Q,p->rChild);
    }
    printf("没有找到该课程");
    return NULL;
}
void RB_Transplant(rbTree &T, rbTNode *u, rbTNode *v){
    if(u->p->cname == "NIL")    T = v;
    else {
        if(u == u->p->lChild)  u->p->lChild = v;
        else u->p->rChild = v;
    }
    v->p = u->p;
    int a = v->ctime2;
    int b=0,c=0;
    if(v->lChild != NULL) b =v->lChild->max;
    if(v->rChild != NULL) c =v->rChild->max;
    v->max = Max(a, b, c);
}
rbTNode *Tree_Min(rbTree T){
    rbTNode *z = T;
    while (z->lChild->cname != "NIL") {
        z = z->lChild;
    }
    return z;
}
void RB_Delete_Fix(rbTree &T, rbTNode *x){
    rbTNode *w;
    while(x != T && x->color == 0){
        if (x == x->p->lChild){
            w = x->p->rChild;
            if(w->cid ==0) return;
            if (w->color == 1){ //情况1，变色左旋转情况2
                w->color = 0;
                x->p->color = 1;
                Left_Rotate(T, x->p);
                w = x->p->rChild;
            }
            if(w->lChild->color == 0 && w->rChild->color == 0){ //情况2，直接上传
                w->color = 1;
                x = x->p;
            }
            else {
                if (w->rChild->color == 0){ //情况3，通过旋转转变为情况4，统一表示
                    w->lChild->color = 0;
                    w->color = 1;
                    Right_Rotate(T, w);
                    w = x->p->lChild;
                }
                w->color = x->p->color;
                x->p->color = 0;
                w->rChild->color = 0;
                Left_Rotate(T, x->p);
                x = T;
            }
        }
        else{
            w = x->p->lChild;
            if(w->cid ==0) return;
            if (w->color == 1){ //情况1，变色左旋转情况2
                w->color = 0;
                x->p->color = 1;
                Right_Rotate(T, x->p);
                w = x->p->lChild;
            }
            if(w->rChild->color == 0 && w->lChild->color == 0){ //情况2，直接上传
                w->color = 1;
                x = x->p;
            }
            else {
                if (w->lChild->color == 0){ //情况3，通过旋转转变为情况4，统一表示
                    w->rChild->color = 0;
                    w->color = 1;
                    Left_Rotate(T, w);
                    w = x->p->rChild;
                }
                w->color = x->p->color;
                x->p->color = 0;
                w->lChild->color = 0;
                Right_Rotate(T, x->p);
                x = T;
            }
        }
    }
    x->color = 0;
}
void RB_Delete(rbTree &T, rbTNode *z){
    rbTNode *y = z;
    rbTNode *x;
    bool y_o_color = y->color;
    if(z->lChild->cname == "NIL"){
        RB_Transplant(T, z, z->rChild);
        x = z->rChild;
    }
    else {
        if (z->rChild->cname == "NIL"){
            RB_Transplant(T, z, z->lChild);
            x = z->lChild;
        }
        else{
            y = Tree_Min(z->rChild);
            x = y->rChild;
            y_o_color = y->color;
            if(y->p == z) x->p = y;     //x = nil
            else{
                RB_Transplant(T, y, y->rChild);
                y->rChild = z->rChild;
                y->rChild->p = y;
            }
            RB_Transplant(T, z, y);
            y->lChild = z->lChild;
            y->lChild->p = y;
            y->color = z->color;
        }
    }
    //    if(z==T){
   // T = y;
//}
    while(y->cname != "NIL"){
        y->max = Max(y->ctime2, y->lChild->max, y->rChild->max);
        y = y->p;
    }
    if(y_o_color == 0) RB_Delete_Fix(T,x);
}
//删除

//查找区间
int Max(int a, int b, int c){
    int d = a;
    if(b>d) d = b;
    if(c>d) d = c;
    return d;
}
bool Overlap(rbTNode *x, int t1, int t2){
    if(x->ctime1<t2 && x->ctime2>t1)    return true;
    else return false;
}
rbTNode *Interval_Search(rbTree T, int t1, int t2){
    rbTNode *x = T;
    while (x->cname!="NIL" && !Overlap(x, t1, t2)) {
        if(x->lChild->cname!="NIL"&&x->lChild->max>=t1)
            x = x->lChild;
        else x = x->rChild;
    }
    return x;
}
//查找区间

//主程序
int main(int argc, const char * argv[]) {
    rbTree T;
    rbTNode *NIL = (rbTree)malloc(sizeof(rbTNode));
    IniNIL(NIL);
    creatrbTree2(T,NIL);
    levelTraversal(T);
    int i;
    while(true){
        printf("插入：1，删除：2，退出：0, 查找区间：3:\n");
        scanf("%d",&i);
        if(i == 1){
            RB_Insert(T,Create_Node());
            levelTraversal(T);
        }
        if(i == 0){
            return 0;
        }
        if(i == 2){
            int id;
            printf("输入ID：");
            scanf("%d", &id);
            if(SortbyID(T,id)!=NULL){
            RB_Delete(T, SortbyID(T,id));
            levelTraversal(T);
            }
        }
        if(i == 3){
            int t1,t2;
            printf("输入区间：");
            scanf("%d %d", &t1, &t2);
            if(Interval_Search(T, t1, t2)->cname == "NIL")  printf("没有时间重叠的课程\n");
            else std::cout << Interval_Search(T, t1, t2)->cname << "\n";
        }
    }
}
