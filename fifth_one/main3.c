#include <stdio.h>
#include <math.h>

int contains_binary(int a)
{
    while (a > 0)
    {
        int mod = a % 1000;
        // printf("mod %i \n", mod);
        if (!(mod == 1 || mod == 10 || mod == 11 || mod == 0 || mod == 100 || mod == 101 || mod == 110 || mod == 111))
        {
            return 0;
        }
        a /= 1000;
    }
    return 1;
}

int main()
{
    int n;
    scanf("%i", &n);
    int digits = 0;
    int count = 0;
    int startPoint = 0;
    if (n == 1)
    {
        printf("1");
        return 0;
    }

    for (int i = 0; i <= 9; i++)
    {
        if (n > 2 * pow(10, i))
        {
            count = pow(2, i + 1);
            startPoint = pow(10, i + 1) + 1;
        }
        else
        {
            break;
        }
    }
    for (int i = startPoint; i <= n; i++)
    {
        count += contains_binary(i);
    }

    // printf("%i \n", startPoint);
    printf("%i", count);
}
