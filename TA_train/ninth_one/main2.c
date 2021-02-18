#include <stdio.h>
#include <math.h>

int clear(int robbers, int levels)
{
    if (!robbers)
    {
        return levels;
    }
    for (int i = 0; i < 11; i++) // max of 2048
    {
        if (robbers >= pow(2, i) && robbers < pow(2, i + 1))
        {
            return clear(robbers - (int)(pow(2, i)), levels + 1);
        }
    }
}

int main()
{
    int n, s, t, robbers_count = 0;
    scanf("%i", &n);
    char street[n + 1];
    scanf("%s", street);
    scanf("%i %i", &s, &t);
    s--;
    t--;
    for (int i = s; i != t; (i > t) ? i-- : i++)
    {
        robbers_count += (street[i] == 'H') ? 1 : 0;
    }
    printf("count %i\n", robbers_count);

    printf("%i", clear(robbers_count, 0));
}