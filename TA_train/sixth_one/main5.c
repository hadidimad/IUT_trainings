#include <stdio.h>

#define F 0
#define S 1
#define D 2

char chefs[3];
int prices[3] = {6000, 18000, 30000};
int materials[3];

void chef(int order)
{
    printf((materials[order]) ? "Food is ready\n" : "Material is not enough\n");
    materials[order]--;
}
void clerk(int order)
{
    if (chefs[order] == 'a')
    {
        printf("Not a chef\n");
    }
    else
    {
        chef(order);
    }
}

void garson(int money, int order)
{
    if (prices[order] > money)
    {
        printf("No enough money\n");
    }
    else
    {
        clerk(order);
    }
}
int order_to_int(char order)
{
    switch (order)
    {
    case 'f':
        return 0;

    case 's':
        return 1;

    case 'd':
        return 2;
    }
}

int main()
{
    int coustomers_count;
    scanf("%i %i %i\n", &materials[F], &materials[S], &materials[D]);
    scanf("%c %c %c\n", &chefs[F], &chefs[S], &chefs[D]);
    scanf("%i\n", &coustomers_count);
    for (int i = 0; i < coustomers_count; i++)
    {
        int money;
        char order;
        scanf("%i %c", &money, &order);
        garson(money, order_to_int(order));
    }
}