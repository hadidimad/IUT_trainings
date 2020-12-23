#include <stdio.h>
int eat_watermelons(int *watermelons, int length)
{
    int first_melon = -1;
    int second_melon = -1;

    for (int i = 0; i < length; i++)
    {
        if (watermelons[i] != 0)
        {
            first_melon = i;
        }
        if (watermelons[i] != 0 && first_melon > 0 && i != first_melon)
        {
            second_melon = i;
        }
    }
}
int eat(int *watermelons, int length, int first, int second)
{
    // printf("discussing: %i %i \n",first,second);
    if (watermelons[first] < watermelons[second])
    {
        // printf("Eated: %i\n",first);
        watermelons[first] = 0;
        if (second < length - 1)
        {
            return eat(watermelons, length, second, second + 1);
        }
        else
        {
            return second;
        }
    }
    else
    {
        // printf("Eated: %i\n",second);
        watermelons[second] = 0;
        if (second < length - 1)
        {
            return eat(watermelons, length, first, second + 1);
        }
        else
        {
            return first;
        }
    }
}
int main()
{
    int n;
    scanf("%i", &n);
    int watermelons[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%i", &watermelons[i]);
    }
    printf("%i", eat(watermelons, n, 0, 1) + 1);
}