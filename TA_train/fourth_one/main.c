#include <stdio.h>

int main()
{
    int m, n;
    long int sum = 0;
    int secondSigma = 0;
    scanf("%i %i", &n, &m);
    for (int j = 1; j <= n; j++)
    {
        for (int i = -10; i <= m; i++)
        {

            sum += ((i + j) * (i + j) * (i + j)) / j * j;
        }
    }
    printf("%ld", sum);
}