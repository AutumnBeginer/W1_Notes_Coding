#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, *arr;
    printf("输入几个数: ");
    scanf("%d", &n); // 输入几个数

    // 动态分配内存
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败\n");
        return 1;
    }

    for (int i = 0; i < n; i++) { // 依次输入n个数组元素
        printf("请输入第%d个数: ", i + 1);
        scanf("%d", &arr[i]);
    }

    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    printf("求和结果为: %d\n", sum); // 求和

    // 释放分配的内存
    free(arr);

    return 0;
}