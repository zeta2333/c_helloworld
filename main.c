#include <stdio.h>

//�����������нϴ��һ��
int max(int a, int b) {
    return a > b ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    int x, y, maxval;
    //���庯��ָ��
    int (*pmax)(int, int) = max;  //Ҳ����д��int (*pmax)(int a, int b)
    int (*s)(int, int) = sum;
    int res = (*s)(2, 3);
    printf("%d\n", res);
    printf("Input two numbers:");
//    scanf("%d %d", &x, &y);
    maxval = (*pmax)(2, 3);
    printf("Max value: %d\n", maxval);
    return 0;
}