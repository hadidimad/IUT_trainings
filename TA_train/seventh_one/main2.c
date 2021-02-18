#include <stdio.h>
#include <math.h>
int primes[4] = {2, 3, 5, 7};
int check_prime(int a)
{
    if (a == 5 || a == 2)
    {
        return 1;
    }
    if (a % 10 == 5 || a % 10 == 2)
    {
        return 0;
    }
    int c;
    if (a == 1)
    {
        return 0;
    }
    for (c = 2; c <= a / 2; c++)
    {
        if (a % c == 0)
            return 0;
    }
    return 1;
}

void generate_pass(int code, int n)
{
    // printf("next function\n");
    
    if ((int)(log10(code)) + 1 == n)
    {

        printf("%i\n", code);
        return;
    }
    

    for (int i = 1; i <= 9; i++)
    {
        code *= 10;
        code += i;
        // printf("code is %i\n", code);
        if (check_prime(code))
        {
            // printf("code is  prime \n");
            generate_pass(code, n);
        }
        code /= 10;
    }
}

int main()
{
    int n;
    scanf("%i",&n);


    generate_pass(0, n);
}