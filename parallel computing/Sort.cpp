// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include <iostream>
#include<omp.h>
#include<time.h>
#include<stdlib.h>

#define NUM_SORT 5000000


/*
 * 将一个数组中的两个相邻有序区间合并成一个
 *
 * 参数说明：
 *     a -- 包含两个有序区间的数组
 *     start -- 第1个有序区间的起始地址。
 *     mid   -- 第1个有序区间的结束地址。也是第2个有序区间的起始地址。
 *     end   -- 第2个有序区间的结束地址。
 */
void merge(int a[], int start, int mid, int end)
{
	int *tmp = (int *)malloc((end - start + 1) * sizeof(int));    // tmp是汇总2个有序区的临时区域
	int i = start;            // 第1个有序区的索引
	int j = mid + 1;        // 第2个有序区的索引
	int k = 0;                // 临时区域的索引

	while (i <= mid && j <= end)
	{
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}

	while (i <= mid)
		tmp[k++] = a[i++];

	while (j <= end)
		tmp[k++] = a[j++];

	// 将排序后的元素，全部都整合到数组a中。
	for (i = 0; i < k; i++)
		a[start + i] = tmp[i];

	free(tmp);
}

/*
 * 归并排序(从上往下)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     start -- 数组的起始地址
 *     endi -- 数组的结束地址
 */
void merge_sort(int a[], int start, int end)
{
	if (a == NULL || start >= end)
		return;

	int mid = (end + start) / 2;
	merge_sort(a, start, mid); // 递归排序a[start...mid]
	merge_sort(a, mid + 1, end); // 递归排序a[mid+1...end]

	// a[start...mid] 和 a[mid...end]是两个有序空间，
	// 将它们排序成一个有序空间a[start...end]
	merge(a, start, mid, end);
}
void Random(int a[], int n) {
	int i = 0;
	srand((unsigned)time(NULL));
	while (i < n) {
		a[i] = rand();
		i++;
	}
}
void merge_sort_parallel1(int a[], int start, int end)
{
	if (a == NULL || start >= end)
		return;

	int mid = (end + start) / 2;
	//printf("id:%d\n", omp_get_thread_num());
	#pragma omp task
	{
		merge_sort_parallel1(a, start, mid);
	}	
	#pragma omp task
	{
		merge_sort_parallel1(a, mid+1, end);
	}
	#pragma omp taskwait
	merge(a, start, mid, end);

}

void merge_sort_parallel2(int a[], int start, int end)
{
	if (a == NULL || start >= end)
		return;

	int mid = (end + start) / 2;
	//printf("id:%d\n", omp_get_thread_num());
	if (end - start < NUM_SORT / 16) {
		merge_sort(a, start, mid);
		merge_sort(a, mid + 1, end); 
	}
	else {
	#pragma omp task
	{
		merge_sort_parallel2(a, start, mid);
	}
	#pragma omp task
	{
		merge_sort_parallel2(a, mid + 1, end);
	}
	#pragma omp taskwait
	}
	merge(a, start, mid, end);

}
void merge_sortpl3(int a[], int start, int end)
{
	if (a == NULL || start >= end)
		return;

	int mid = (end + start) / 2;

	merge_sortpl3(a, start, mid);
	merge_sortpl3(a, mid + 1, end);

	merge(a, start, mid, end);

}
void merge_sort_parallel3(int a[]) {
	int i;
#pragma omp parallel for
		for (i = 0; i < 8; i++) {
			merge_sortpl3(a, i * NUM_SORT/8, i * NUM_SORT/8 + NUM_SORT/8 - 1);
		}
#pragma omp parallel for
		for(i = 0; i < 4; i++){
			merge(a, i * NUM_SORT/4, i * NUM_SORT/4 + NUM_SORT/8-1, i * NUM_SORT/4 + NUM_SORT/4 - 1);
}
#pragma omp parallel for
                for(i = 0; i < 2; i++){
                        merge(a, i * NUM_SORT/2, i * NUM_SORT/2 + NUM_SORT/4-1, i * NUM_SORT/2 + NUM_SORT/2 - 1);
}
merge(a, 0, NUM_SORT/2 -1, NUM_SORT);
}

int a[NUM_SORT];

int main()
{

	//串行
	int i;
	Random(a, NUM_SORT);
	printf("init done\n");
	printf("Threads num:%d\n", omp_get_max_threads());
	static int a2[NUM_SORT];
	for (i = 0; i < NUM_SORT;  i++) a2[i] = a[i];
	static int a3[NUM_SORT];
	for (i = 0; i < NUM_SORT; i++) a3[i] = a[i];
	static int a4[NUM_SORT];
	for (i = 0; i < NUM_SORT; i++) a4[i] = a[i];
	printf("copy done\n");
	double start_time = omp_get_wtime();
	merge_sort(a, 0, NUM_SORT - 1);
	double end_time = omp_get_wtime();
	printf("time:%fms\n", (end_time - start_time) * 1000);
	//for (i = 0; i < 10; i++) printf("%d	", a[i]);

	//直接并行
	//omp_set_num_threads(NUM_THREADS);
	start_time = omp_get_wtime();
	#pragma omp parallel num_threads(10)
	{	
		#pragma omp single
		{
			merge_sort_parallel1(a2, 0, NUM_SORT - 1);
		}
	}
	end_time = omp_get_wtime();
        printf("time:%fms\n", (end_time - start_time) * 1000);

	//有限线程（8）的并行
	start_time = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		{
			merge_sort_parallel2(a3, 0, NUM_SORT - 1);
		}
	}
	end_time = omp_get_wtime();
    printf("time:%fms\n", (end_time - start_time) * 1000);

	//手动分割
	start_time = omp_get_wtime();
	merge_sort_parallel3(a4);
	end_time = omp_get_wtime();
    printf("time:%fms\n", (end_time - start_time) * 1000);
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
/*
#pragma omp parallel private(aa[i])
{
	merge_sort_pl3(aa[i], start, end);
	for (j = 0; j < NUM_SORT / 8; j++)
		a[i*NUM_SORT / 8 + j] = aa[i][j];
}
*/
// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
