#include <stdio.h>

int len(char *a)
{
    int i = 0;
    while (a[i])
    {
        i++;
    }
    return i;
}

int main()
{
    char N[15];
    scanf("%s", N);
    int length = len(N);
    int isEqual = 1;

    for (int i = 0; i < length; i++)
    {
        if (N[i] != N[length - i-1])
        {
            isEqual = 0;
        }
    }
    printf((isEqual) ? "YES" : "NO");
}