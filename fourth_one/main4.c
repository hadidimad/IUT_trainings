#include <stdio.h>

int main()
{
    int width;
    scanf("%i", &width);
    int pen = 0;

    int space = (width / 2);
    int reverse = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < space; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < (width)-space * 2; j++)
        {
            printf("*");
        }
        for (int j = 0; j < space; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < space; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < width - space * 2; j++)
        {
            printf("*");
        }
        for (int j = 0; j < space; j++)
        {
            printf(" ");
        }
        printf("\n");
        if (space == 0)
        {
            reverse = 1;
        }
        space += (reverse) ? +1 : -1;
    }
}