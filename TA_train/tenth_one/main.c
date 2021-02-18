#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int quickSort_partition(int *array, int p, int q)
{
    int x = array[p];
    int i = p;
    for (int j = p + 1; j <= q; j++)
    {
        if (array[j] <= x)
        {
            i++;
            int temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            // swap(array[i], array[j]);
        }
    }
    int temp = array[p];
    array[p] = array[i];
    array[i] = temp;
    // swap(array[i], array[p]);
    return i;
}

void quickSort(int *array, int p, int r)
{
    int q;
    if (p < r)
    {
        q = quickSort_partition(array, p, r);
        quickSort(array, p, q - 1);
        quickSort(array, q + 1, r);
    }
}

int main()
{
    char temp = 0;
    int numbers[500001];
    int size = 0;
    int value;
    char c;
    // while (c != '\n' && c != EOF)
    // {
    //     scanf("%d%c", &value, &c);
    //     numbers[size] = value;
    //     size++;
    // }

    while (scanf("%i", &value) != EOF)
    {
        numbers[size] = value;
        size++;
    }

    quickSort(numbers, 0, size - 1);
    for (int i = 0; i < size; i++)
    {
        printf("%i ", numbers[i]);
    }
}