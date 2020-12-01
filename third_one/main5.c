#include <stdio.h>

int main()
{
    int a, b;

    scanf("%i %i", &a, &b);
    if (b >= a)
    {
        printf("Wrong order!");
    }
    else if ((a - b) % 2 != 0)
    {
        printf("Wrong difference!");
    }
    else
    {
        int boderWidth = (a - b) / 2;
        for (int i = 0; i < a; i++)
        {
            if (i < boderWidth)
            {
                for (int j = 0; j < a; j++)
                {
                    printf("* ");
                }
                printf("\n");
            }
            else if (a - i <= boderWidth)
            {

                for (int j = 0; j < a; j++)
                {
                    printf("* ");
                }
                printf("\n");
            }
            else
            {
                for (int j = 0; j < a; j++)
                {
                    if (j < boderWidth)
                    {
                        printf("* ");
                    }
                    else if (a - j <= boderWidth)
                    {
                        printf("* ");
                    }
                    else
                    {
                        printf("  ");
                    }
                }
                printf("\n");
            }
        }
    }

    return 0;
}