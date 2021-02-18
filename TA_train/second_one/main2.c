#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%i %i %i", &a, &b, &c);
    printf((a + b + c == 180 && a != 0 && b != 0 && c != 0) ? "Yes":"No");

    return 0;
}