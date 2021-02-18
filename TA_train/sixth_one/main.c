#include <stdio.h>

long long int factorial(long long int n)
{
    if (n == 0)
        return 1;
    else
        return (n * factorial(n - 1));
}

long long int power(long long int x, long long int y)
{
    if (y == 0)
    {
        return 1;
    }
    else if (y == 1)
    {
        return x;
    }
    long long int initX = x;

    for (int i = 1; i < y; i++)
    {
        x *= initX;
    }
    return x;
}

float get_eX(long long int x, int max_level, int current_level)
{

    if (current_level == max_level)
    {
        return (float)((float)(power(x, current_level)) / ((float)(factorial(current_level))));
    }

    return (float)((float)power(x, current_level) / (float)factorial(current_level)) + (float)(get_eX(x, max_level, current_level + 1));
}

int main()
{

    int x, n;
    scanf("%i %i", &x, &n);
    if (n == 0)
    {
        printf("%.3f",1.0);
        return 0;
    }
    printf("%.3f", get_eX(x, n - 1, 0));
}