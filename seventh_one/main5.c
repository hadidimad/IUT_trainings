#include <stdio.h>

int fib(int a, int b, int lvl, int n)
{
    return (lvl == n - 1) ? a : fib(a, b + a, lvl + 1, n);
}

int fibo(int n)
{
    return (n == 1 || n == 0) ? n : fibo(n - 1) + fibo(n - 2);
}

int main()
{
    int n;
    scanf("%i", &n);
    printf("%i", fibo(n));
}