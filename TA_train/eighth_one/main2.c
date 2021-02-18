#include <stdio.h>

void ShowFibNth(long int a, long int b)
{
    if (a == 0)
    {
        return;
    }
    else
    {
        printf("%li\n", a);
    }

    ShowFibNth(b - a, a);
}

int main()
{
    int a, b;
    scanf("%i %i", &a, &b);
    ShowFibNth(a, b);
}