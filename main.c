#include <stdio.h>

//返回两个数中较大的一个
int max(int a, int b) {
    return a > b ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    int x, y, maxval;
    //定义函数指针
    int (*pmax)(int, int) = max;  //也可以写作int (*pmax)(int a, int b)
    int (*s)(int, int) = sum;
    int res = (*s)(2, 3);
    printf("%d\n", res);
    printf("Input two numbers:");
//    scanf("%d %d", &x, &y);
    maxval = (*pmax)(2, 3);
    printf("Max value: %d\n", maxval);
    return 0;
}