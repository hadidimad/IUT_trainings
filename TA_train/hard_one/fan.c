#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {

            if (i == j || j == 0 || i == n - 1)
            {
                printf("* ");
            }
            else
            {
                printf("  ");
            }
        }
        for (int j = 0; j < n; j++)
        {

            if (i == n - j - 1 || j == 0 || i == 0)
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
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (i == n - j - 1 || j == n - 1 || i == n - 1)
            {
                printf("* ");
            }
            else
            {
                printf("  ");
            }
        }

        for (int j = 0; j < n; j++)
        {

            if (i == j || j == n - 1 || i == 0)
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