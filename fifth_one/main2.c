#include <stdio.h>

char *keep_chocolate(int a1, int a2, int a3)
{
    //first step : sell all of other chocolates and buy first one
    int can_keep = 0;
    while (a2 && a3)
    {
        a2--;
        a3--;
        a1++;
    }
    return (!(a2 % 2) && !(a3 % 2) && (a1 % 2)) ? "YES" : "NO";
}

int main()
{
    int a1, a2, a3;
    scanf("%i %i %i", &a1, &a2, &a3);
    printf("%s %s %s", keep_chocolate(a1, a2, a3), keep_chocolate(a2, a1, a3), keep_chocolate(a3, a2, a1));
}