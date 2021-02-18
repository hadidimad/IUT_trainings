#include <stdio.h>

long long int go_to_single_digit(long long int n)
{
    if (n < 10)
    {
        return n;
    }
    else
    {
        long long int temp = n;
        long long int sum = 0;
        while (temp)
        {
            sum += temp % 10;
            temp /= 10;
        }
        return go_to_single_digit(sum);
    }
}

int main()
{
    long long int in;
    scanf("%lli",&in);
    printf("%lli",go_to_single_digit(in));
    
}