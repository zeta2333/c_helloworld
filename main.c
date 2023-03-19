#include<stdio.h>
int main(){
    int sum = 103;  //总数
    int count = 7;  //数目
    double average;  //平均数
    char* str = (char *)sum;
    average = (double) sum / count;
    printf("Average is %lf!\n", average);
    return 0;
}