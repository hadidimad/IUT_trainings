#include <stdio.h>
int get_index(int i, int size)
{
    while (i >= size)
    {
        i -= size;
    }
    return i;
}

int vote(int *mafias, int i, int should_remove, int size, int remain)
{

    while (!mafias[get_index(i, size)])
    {
        i++;
    }
    if (remain == 1)
    {
        return get_index(i, size);
    }
    if (should_remove)
    {
        mafias[get_index(i, size)] = 0;
        // printf("removing %i\n", get_index(i, size));
        remain--;
        should_remove = !should_remove;
    }
    else
    {
        should_remove = !should_remove;
    }
    return vote(mafias, i + 1, should_remove, size, remain);
}

int main()
{
    int n;
    scanf("%i", &n);
    int mafias[n];
    for (int i = 0; i < n; i++)
    {
        mafias[i] = 1;
    }

    printf("%i", vote(mafias, 1, 1, n, n) +1);
}