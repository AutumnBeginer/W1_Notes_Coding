#include <stdio.h>

int main() {
    // 输入一个正整数 n，然后输入 n 个整数，输出它们的最大值
    // 例如：输入 3\n10 20 5，输出 20
    int n;
    scanf("%d", &n);
    int max_val;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (i == 0 || x > max_val) {
            max_val = x;
        }
    }
    printf("%d\n", max_val);
}
