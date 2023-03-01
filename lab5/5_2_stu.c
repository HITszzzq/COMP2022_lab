#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

void HeapAdjust(int *arr,int s,int m)
{
    int rc = arr[s];
    for(int j = 2 * s;j <= m;j *= 2)
    {
        if(j < m && arr[j] < arr[j + 1])
        {
            ++j;
        }
        if(rc >= arr[j])
        {
            break;
        }
        arr[s] = arr[j];
        s = j;
    }
    arr[s] = rc;
    return;
}

//Todo
//需要返回一个数组，数组元素是原始数组里最大的k个数
//注意按照从小到大的顺序排序
//可以自行添加其他辅助函数,可以根据实际需要修改函数参数
int *solve2(int *arr,int N,int k){
    static int ans[MAX];
    for(int i = 0;i < N;i++)
    {
        ans[i] = 0;
    }
    int *p = NULL;
    p = ans;
    for(int i = (N - 1) / 2;i >= 0;--i)
    {
        HeapAdjust(arr,i,N - 1);
    }
    for(int i = N - 1;i > N - 1 - k;--i)
    {
        ans[k - N + i] = arr[0];
        arr[0] = arr[i];
        HeapAdjust(arr,0,i - 1);
    }
    printf("\n");
    return p;
}

void test2(){
	int caseNum; //表示测试轮数
	if (freopen("5_2_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_2_input_5.in");
    }
	scanf("%d", &caseNum);
    int case1 = 0;
    for (; case1 < caseNum; case1++) {
		int k, N;
        scanf("%d%d", &k, &N);
        int arr[MAX];
        int i = 0;
        for (; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        int *res = solve2(arr,N,k);
		printf("==== Case %d ====\nres : ", case1 + 1);
        for (i = 0; i < k; i++) {
            printf("%d ",res[i]);
        }
    }
	fclose(stdin);
}


int main(void) {
    test2();
    return 0;
}
