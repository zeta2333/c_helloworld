#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;
    if ((fp = fopen("./demo.txt", "r")) == NULL) {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    return 0;
}