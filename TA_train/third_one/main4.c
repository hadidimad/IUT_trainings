#include <stdio.h>
//finds B M M and always a >= b
long int findBmm(long int a, long int b)
{

    if (b == 0)
    {
        return a;
    }
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        findBmm(b, a % b);
    }
}

int main()
{
    long int a, b;
    scanf("%li %li", &a, &b);
    a = (a < 0) ? a * -1 : a;
    b = (b < 0) ? b * -1 : b;
    long int out = (a > b) ? findBmm(a, b) : findBmm(b, a);
    printf("%li", out);

    return 0;
}