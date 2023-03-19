#include <stdio.h>

int main() {
    float a = 0.302;
    float b = 128.101;
    double c = 123;
    float d = 112.64E3;
    double e = 0.7623e-2;
    float f = 1.23002398;
    printf("a=%e \nb=%f \nc=%lf \nd=%lE \ne=%lf \nf=%f\n", a, b, c, d, e, f);
    return 0;
}

