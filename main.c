#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;
    if ((fp = fopen("./demo.txt", "r")) == NULL) {
        printf("打开文件失败\n");
        exit(0);
    }
    return 0;
}