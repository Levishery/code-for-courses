#include <cuda_runtime.h>
#include "device_launch_parameters.h"

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

#define WIDTH 512
#define LIMIT 40
#define WINSIZE 12

#define BLOCK_SIZE 512

int** sad(int view1[WIDTH][WIDTH], int view5[WIDTH][WIDTH]);

__global__ void sad_gpu(int* dis, int* v1, int* v5, int width){
	//每行共享存储
	__shared__ int v1_c[WINSIZE][WIDTH];
	__shared__ int v5_c[WINSIZE][WIDTH];
	//同一行用一个block中的线程计算
	int bi = blockIdx.x;
//	printf("id: %d", bi);
	//一行中的每个像素对应视差用不同thread计算
	int tj = threadIdx.x;
	//每个线程取它对应的像素列
	for(int k = 0; k < WINSIZE; k++){
		v1_c[k][tj] = v1[(bi+k)*WIDTH + tj];
		v5_c[k][tj] = v5[(bi+k)*WIDTH + tj];
	}
	__syncthreads();	//等所有都取完再计算
	//每不越界的线程计算滑窗像素和，找出最接近的
	if(tj < WIDTH-WINSIZE){
		int min = 2550000;
		int min_index = 0;
		for(int k = 0; k < LIMIT; k++){	//滑窗
			unsigned int result = 0;
			for(int m = 0; m < WINSIZE; m++){
				for(int l = 0; l < WINSIZE; l++ ){
					result = __sad(v5_c[m][tj+l], v1_c[m][tj+k+l], result);
				}
			}
			if(result < min){
				min = result;
				min_index = k;
			}
		}
//		printf("%d	",min_index);
		dis[bi*WIDTH+tj] = min_index; 		
	}
}

__global__ void sad_gpu_without_sm(int* dis, int* v1, int* v5, int width){
        int bi = blockIdx.x;
        int tj = threadIdx.x;
        if(tj < WIDTH-WINSIZE){
                int min = 2550000;
                int min_index = 0;
                for(int k = 0; k < LIMIT; k++){ //?~Q窪
                        unsigned int result = 0;
                        for(int m = 0; m < WINSIZE; m++){
                                for(int l = 0; l < WINSIZE; l++ ){
                                        result = __sad(v5[(bi+m)*WIDTH+tj+l], v1[(bi+m)*WIDTH+tj+k+l], result);
                                }
                        }
                        if(result < min){
                                min = result;
                                min_index = k;
                        }
                }
                dis[bi*WIDTH+tj] = min_index;
        }
}

__global__ void sad_gpu2(int* dis, int* v1, int* v5, int width){
        //每行共享存储
        __shared__ int v1_c[WIDTH];
        __shared__ int v5_c[WIDTH];
        //同一行用一个block中的线程计算
        int bi = blockIdx.x;
//      printf("id: %d", bi);
        //一行中的每个像素对应视差用不同thread计算
        int tj = threadIdx.x;
        //每个线程取它对应的像素列计算和
        for(int k = 0; k < WINSIZE; k++){
                v1_c[tj] += v1[(bi+k)*WIDTH + tj];
                v5_c[tj] += v5[(bi+k)*WIDTH + tj];
        }
        __syncthreads();        //等所有都取完再计算
        //每不越界的线程计算滑窗像素和，找出最接近的
        if(tj < WIDTH-WINSIZE){
                int min = 2550000;
                int min_index = 0; 
                for(int k = 0; k < LIMIT; k++){ //滑窗
                        unsigned int result = 0;
                                for(int l = 0; l < WINSIZE; l++ ){
                                        result = __sad(v5_c[tj+l], v1_c[tj+k+l], result);
                                }
                        if(result < min){
                                min = result;
                                min_index = k;
                        }
                }
//              printf("%d      ",min_index);
                dis[bi*WIDTH+tj] = min_index;
        }
}

	
int main()
{
	FILE *view1 = NULL;
	FILE *dis = NULL;
	view1 = fopen("view1.txt", "r");
	static int view1_[WIDTH][WIDTH];
	int i, j;
	char buff;
	for (i = 0; i < WIDTH; i++) {
		for (j = 0; j < WIDTH; j++)
			fscanf(view1, "%d " ,&view1_[i][j]);
		fscanf(view1, "%c", &buff);
	}
	//printf("%d %d\n", view1_[0][0], view1_[511][511]);
	fclose(view1);
	FILE *view5 = NULL;
	view5 = fopen("view5.txt", "r");
	static int view5_[WIDTH][WIDTH];
	for (i = 0; i < WIDTH; i++) {
		for (j = 0; j < WIDTH; j++)
			fscanf(view5, "%d ", &view5_[i][j]);
		fscanf(view5, "%c", &buff);
	}
	//printf("%d %d\n", view5_[0][0], view5_[511][511]);
	fclose(view5);
	int **disp;
	clock_t startTime = clock();	//计时
	disp = sad(view1_, view5_);
	clock_t endTime = clock();
        double CPUtime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("CPU:%f\n", CPUtime);
	dis = fopen("disp.txt","w");
	for (i = 0; i < WIDTH; i++) {
                for (j = 0; j < WIDTH; j++)
                        fprintf(dis, "%d " ,disp[i][j]);
                fprintf(view1, "\n");
//		printf("write %d\n", i);
        }
	printf("write done\n");
	fclose(dis);
	
	//并行
	//把数据做成一维
	unsigned int size_im = sizeof(int)*WIDTH*WIDTH;
	int *h_1 = (int*)malloc(sizeof(int)*WIDTH*WIDTH);
	int *h_5 = (int*)malloc(sizeof(int)*WIDTH*WIDTH);
	for(i = 0; i < WIDTH*WIDTH; i++){
		h_1[i] = view1_[i/WIDTH][i-(i/WIDTH)*WIDTH];
		h_5[i] = view5_[i/WIDTH][i-(i/WIDTH)*WIDTH];
	}
	//分配设备内存
//	startTime = clock();
	int* d_1;
	cudaMalloc((void**)&d_1, size_im);
	int* d_5;
	cudaMalloc((void**)&d_5, size_im);
	//拷贝数据到设备
	cudaMemcpy(d_1, h_1, size_im, cudaMemcpyHostToDevice);
	cudaMemcpy(d_5, h_5, size_im, cudaMemcpyHostToDevice);
	//分配结果所需空间
	int* d_dis;
	cudaMalloc((void**)&d_dis, size_im);
	int* h_dis = (int*)malloc(size_im);
	//计时
	startTime = clock();
	//设置block，thread数
	dim3 threads(WIDTH);
	dim3 grid(WIDTH-WINSIZE);
	printf("begin gpu computation\n");
	sad_gpu_without_sm<<< grid, threads>>>(d_dis, d_1, d_5, WIDTH);
	cudaThreadSynchronize();
	//停止计时
	endTime = clock();
	double GPUtime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	printf("GPU:%f\n", GPUtime);
	//把结果拷贝到主机
	cudaMemcpy(h_dis, d_dis, size_im, cudaMemcpyDeviceToHost);
	//写入文件
        dis = fopen("disp_gpu.txt","w");
        for (i = 0; i < WIDTH*WIDTH; i++) {
	//	if(h_dis[i]>WINSIZE||h_dis[i]<0)
	//		fprintf(dis, "0 ");
	//	else
        		fprintf(dis, "%d " ,h_dis[i]);
        }
        fclose(dis);
	//结束
	free(h_1);
	free(h_5);
	free(h_dis);
	cudaFree(d_1);
	cudaFree(d_5);
	cudaFree(d_dis);

	cudaThreadExit();

	return 0;
}

int** sad(int view1[WIDTH][WIDTH], int view5[WIDTH][WIDTH])
{
		int i, j;	//全图
		int k, l;	//窗口大小
		int n;	//搜索范围
		int result;	//搜索范围内每个窗口的差别
		int min, min_index;		//查找最小值的位置：视差
		int **disp = (int**)malloc(sizeof(int*)*WIDTH);
		for(i = 0; i < WIDTH; i++)
		{
		*(disp+i) = (int*)malloc(sizeof(int)*WIDTH);//开辟列
		}
		for (i = 0; i < WIDTH-WINSIZE; i++) {
			for (j = 0; j < WIDTH-WINSIZE-LIMIT; j++) {
			//对该位置搜索视差
				min = 25500000;
                                min_index = 0;
				for(n = 0; n < LIMIT; n++){
				//每个对应像素求差的绝对值，对整个窗口求和
					result = 0;
					for(k = 0; k<WINSIZE; k++)
						for(l = 0; l<WINSIZE; l++){
					//printf("%d ", view5[i+k][j+l]);	
					result = result + abs(view5[i+k][j+l] - view1[i+k][j+l+n]);
						}
						//printf("%d ",result);
						if(result < min){
							min = result;
							min_index = n;
					//		printf("n: %d, index: %d,re:%d	", n1, min_index, min);
						}
					//	n1++;printf("n1++ ");	//如果更小就更新	
				}
				//printf("%d %d	", min_index, min);
				disp[i][j] = min_index;			
			}
//		printf("roll %d  done\n", i);
		}
		return disp;
}


