//
//  main.cpp
//  算法导论
//
//  Created by Jane Chen on 2019/4/12.
//  Copyright © 2019年 Jane Chen. All rights reserved.
//


#include<cstdlib>
#include<time.h>
#include<cstdio>
#include<iostream>
#include<math.h>

using namespace std;
// 生成元素为随机数的数组
void Random(int a[],int n)
{
    int i=0;
    srand( (unsigned)time( NULL ) );
    while(i<n)
    {
        a[i++]=rand();
    }
}

void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
    int i,j,k;
    
    // i - to mark the index of left aubarray (L)
    // j - to mark the index of right sub-raay (R)
    // k - to mark the index of merged subarray (A)
    i = 0; j = 0; k =0;
    
    while(i<leftCount && j< rightCount) {
        if(L[i]  < R[j]) A[k++] = L[i++];
        else A[k++] = R[j++];
    }
    while(i < leftCount) A[k++] = L[i++];
    while(j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers.
void MergeSort(int *A,int n) {
    int mid,i, *L, *R;
    if(n < 2) return; // base condition. If the array has less than two element, do nothing.
    
    mid = n/2;  // find the mid index.
    
    // create left and right subarrays
    // mid elements (from index 0 till mid-1) should be part of left sub-array
    // and (n-mid) elements (from mid to n-1) will be part of right sub-array
    L = new int[mid];
    R = new int [n - mid];
    
    for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
    for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray
    
    MergeSort(L,mid);  // sorting the left subarray
    MergeSort(R,n-mid);  // sorting the right subarray
    Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
    // the delete operations is very important
    delete [] R;
    delete [] L;
}

void print(int a[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%6d   ", a[i]);
    printf("\n");
}
void quickSort(int a[],int left,int right)
{
    int i,j,temp;
    i=left;
    j=right;
    temp=a[left];//保存轴值
    if(left>right)
        return;
    while(i!=j)/*找到最终位置*/
    {
        while(a[j]>=temp && j>i)
            j--;
        if(j>i)
            a[i++]=a[j];
        while(a[i]<=temp && j>i)
            i++;
        if(j>i)
            a[j--]=a[i];
        
    }
    a[i]=temp;//轴值放回合适的位置
    quickSort(a,left,i-1);/*递归左边*/
    quickSort(a,i+1,right);/*递归右边*/
}
void InsertSort(int a[], int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = a[j]; //待排序第一个元素
        int i = j - 1;  //代表已经排过序的元素最后一个索引数
        while (i >= 0 && key < a[i])
        {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;//找到合适的位置了，赋值,在i索引的后面设置key值。
    }
}

void maxheap_down(int a[], int start, int end)
{
    int c = start;            // 当前(current)节点的位置
    int l = 2*c + 1;        // 左(left)孩子的位置
    int tmp = a[c];            // 当前(current)节点的大小
    for (; l <= end; c=l,l=2*l+1)
    {
        // "l"是左孩子，"l+1"是右孩子
        if ( l < end && a[l] < a[l+1])
            l++;        // 左右两孩子中选择较大者，即m_heap[l+1]
        if (tmp >= a[l])
            break;        // 调整结束
        else            // 交换值
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
}


void heapsort(int a[], int n)
{
    int i;
    
    // 从(n/2-1) --> 0逐次遍历。遍历之后，得到的数组实际上是一个(最大)二叉堆。
    for (i = n / 2 - 1; i >= 0; i--)
        maxheap_down(a, i, n-1);
    
    // 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for (i = n - 1; i > 0; i--)
    {
        // 交换a[0]和a[i]
        swap(a[0], a[i]);
        maxheap_down(a, 0, i-1);
    }
}

/*int main()
{   int i,j;
    double time_total[7][10] = {0};
    for (j=0; j<10; j++){
        int num[7] = {1000, 10000, 50000, 100000, 200000, 500000, 1000000};
        int a[1000000] = {0};
        Random(a,1000000);
        for (i=0; i<7; i++){
            clock_t t1 = clock();
            //quickSort(a, 0, num[i]);
            //InsertSort(a, num[i]);
            //MergeSort(a, num[i]);
            heapsort(a, num[i]);
            double time = double(clock() - t1) / CLOCKS_PER_SEC * 1000 ;
            time_total[i][j] = time;
            printf("time: %f ms\n", time);
        }
    }
    //int num_test = 10;
    //quickSort(a, 0, num[i]);
    //InsertSort(a, num[i]);
    //MergeSort(a, num[i]);
    //heapsort(a, num_test);
    double time_ave[7] = {0};
    double time_dev[7][11] = {0};
    for(i=0; i<7; i++){
        for(j=0; j<10; j++){
//printf("%f  ",time_total[i][j]   );
            time_ave[i] = time_ave[i] + time_total[i][j];
        }
        time_ave[i] /= 10;
        for(j=0; j<10; j++){
            time_dev[i][j] = (time_ave[i] - time_total[i][j]) *(time_ave[i] - time_total[i][j]);
            time_dev[i][10] = time_dev[i][10] + time_dev[i][j];
        }
        time_dev[i][10] = sqrt(time_dev[i][10])/10;
        printf(" %f  ", time_ave[i]);
    }
    for(j=0; j<7; j++){
        printf("%f  ", time_dev[j][10]);
    }
    
    return 0;
}*/

int main(){
    int num_test = 10;
    int a[10] = {0};
    int i = 4;
    Random(a,10);
    if (i==1){
    quickSort(a, 0, num_test);
    printf("quiksort\n");
    print(a, num_test);
    }
    if(i == 2){
    InsertSort(a, num_test);
    printf("insertsort\n");
    print(a, num_test);
    }
    if(i==3){
    MergeSort(a, num_test);
    printf("mergesort\n");
    print(a, num_test);
    }
    if(i==4){
    heapsort(a, num_test);
    printf("heapsort\n");
    print(a, num_test);
    }
}

