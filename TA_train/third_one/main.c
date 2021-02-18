#include <stdio.h>
#include <math.h>

int main()
{
    int N;
    int sum = 0;
    scanf("%i", &N);
    for (int i = 1; i < N; i++)
    {
        if (N % i == 0)
        {
            sum += i;
        }
    }
    printf((sum == N) ? "YES" : "NO");
}