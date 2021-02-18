#include <stdio.h>

long get_pascal_cell(int n, int i)
{
    if (n == i || i == 0)
        return 1;
    else
        return get_pascal_cell(n - 1, i) + get_pascal_cell(n - 1, i - 1);
}

int main()
{
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {

            printf("%li", get_pascal_cell(i, j));
            if (i != j)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
