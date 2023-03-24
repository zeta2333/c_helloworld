/*
// Created by 20237 on 2023/3/24.
*/
//求m到n的和
int sum(int m, int n) {
    if (m > n)return sum(n, m);
    int sum = 0, i;
    for (i = m; i <= n; i++) {
        sum += i;
    }
    return sum;
}