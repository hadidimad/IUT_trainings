#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%i %i %i", &a, &b, &c);
    if (a >= b && a >= c)
    {
        printf((a * a == (b * b + c * c)) ? "YES" : "NO");
    }
    else if (b >= a && b >= c)
    {
        printf((b * b == (a * a + c * c)) ? "YES" : "NO");
    }else{
        printf((c * c == (a * a + b * b)) ? "YES" : "NO");

    }

    return 0;
}