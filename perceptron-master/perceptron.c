//
//  main.c
//  mlp_c
//
//  Created by Jane Chen on 2018/11/11.
//  Copyright © 2018年 Jane Chen. All rights reserved.
//

#include <stdio.h>
int print_w(int w[]){
    int i;
    for (i = 0; i < 4; i++)
        printf("%4d ",w[i]);
    printf("   ");
    return 0;
}
int copy_w(int w1[], int w2[]){
    int i;
    for (i = 0; i < 4; i++)
        w1[i] = w2[i];
    return 0;
}
int* add_w_byr(int w[], int x[], int r){
    int i;
    int w1[4];
    copy_w(w1, w);
    for (i = 0; i < 4; i++)
        w1[i] += r*x[i];
    return w1;
}
int main(int argc, const char * argv[]) {
    // w1={(0,0),(0,1)}
    //w2={(1,0),(1,1)}
    int x[4][4] = {{0, 0, 1, 1}, {0,1,1,1},{1,0,1,1},{1,1,1,1}};
    int i,j;//增广，w2*-1
    for(i = 2; i < 4; i++)
        for(j = 0; j <4; j++)
            x[i][j] = -x[i][j];
    int w[41][4] = {0};
    for(i = 0; i <4; i++)//w0 = (1,1,1,1)
        w[0][i] = 1;
    int r = 1;// r =1
    int k = 1;// 第k轮
    int s = 1;// 第s步
    int flag = 0;
    int Jx;
    printf("样本                          判别函数    更新后权重\n");
    while( k<10 && flag<4){
        flag = 0;
        printf("*******%d*******\n",k);
        for(i = 0; i < 4; i++){
            Jx = 0;
            printf("x%d    ",i);
            print_w(x[i]);
            for(j = 0; j<4 ;j++)
                Jx += x[i][j]*w[s-1][j];
            if(Jx > 0){
                printf("%4d    ",Jx);
                copy_w( w[s], w[s-1]);
                print_w(w[s]);
                flag ++;
            }
            else{
                printf("%4d    ",Jx);
                copy_w( w[s], add_w_byr(w[s-1], x[i], r));
                print_w(w[s]);
            }
            s ++;
            printf("\n");
        }
        k++;
    }
    printf("判别函数：Jx = %dx1 + %dx2\n", w[s-1][0], w[s-1][1]);
    return 0;
}
