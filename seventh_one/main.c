#include <stdio.h>
#include <math.h>

long long int count_binary(char *input, int a, int b)
{
    // printf("%s  | %i   %i\n", input, a, b);
    if (b - a == 0)
    {
        return (input[a] == '0') ? 0 : 1;
    }
    else
    {
        if (input[a] == '0')
        {
            return 0 + count_binary(input, a + 1, b);
        }
        else if (input[a] == '1')
        {
            return (long long int)(pow(2, (b - a))) + count_binary(input, a + 1, b);
        }
        else
        {
            for (int i = a; i <= b; i++)
            {
                input[i] = '1';
            }
            return (long long int)(pow(2, (b - a))) + count_binary(input, a + 1, b);
        }
    }
}

int main()
{
    char a[1000];
    int len = 0, i;
    scanf("%s", a);
    for (i = 0; a[i]; i++)
        ;
    len = i;
    // printf("%i\n", len);
    printf("%lli", count_binary(a, 0, len - 1));
}