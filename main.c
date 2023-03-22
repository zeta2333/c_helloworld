#include <stdio.h>

int main() {
    int n = 0;
    printf("Input a string:");
    while (getchar() != '\n') n++;
    printf("Number of character:%d", n);
    return 0;
}