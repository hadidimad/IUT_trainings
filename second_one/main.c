#include <stdio.h>

int main()
{
    int x1, y1, x2, y2;
    scanf("%i %i %i %i", &x1, &y1, &x2, &y2);
    if (x1 == x2)
    {
        printf("Vertical");
    }
    else if (y1 == y2)
    {
        printf("Horizontal");
    }
    else
    {
        printf("Try again");
    }

    return 0;
}