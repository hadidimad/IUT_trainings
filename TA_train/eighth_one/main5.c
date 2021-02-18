#include <stdio.h>
#include <limits.h>

int get_max(int *values, int length, int n, int last_max)
{
    int max = INT_MIN;
    int start_point;
    for (int start_point = 0; start_point <= length - n; start_point++)
    {
        int sum = 0;
        for (int i = start_point; i < start_point + n; i++)
        {

            sum += values[i];
        }
        if (sum >= max)
        {
            max = sum;
        }
    }
    if (n == length)
    {
        return (max > last_max) ? max : last_max;
    }
    get_max(values, length, n + 1, (max > last_max) ? max : last_max);
}

int main()
{
    int n;
    scanf("%i", &n);
    int values[n];
    int all_minus = 1;
    for (int i = 0; i < n; i++)
    {
        scanf("%i", &values[i]);
        if (values[i] > 0)
        {
            all_minus = 0;
        }
    }
    printf("%i", (all_minus) ? 0 : get_max(values, n, 1, INT_MIN));
}