#include <stdio.h>

int use_complement(int n)
{
    return 3 * n + 3;
}

int main()
{
    long int n;
    scanf("%li", &n);

    while (1)
    {
        if (!(n % 2))
        {
            n /= 2; // exercises
        }
        else
        {
            
            n = use_complement(n);
        }
        if (n == 1)
        {
            printf("Yes");

            break;
        }
        else if (!(n % 3))
        {
            printf("No");
            break;
        }
        // printf("%li\n", n);
        // getchar();
    }
}