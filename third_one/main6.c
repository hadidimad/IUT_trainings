#include <stdio.h>

int main()
{
    int a, b, c, d;
    scanf("%i %i %i %i", &a, &b, &c, &d);
    if (a == 3 && b == 1 & c == 4 && d == 2)
    {
        printf("YES");
    }
    else if (a == 2 && b == 4 & c == 1 && d == 3)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
}