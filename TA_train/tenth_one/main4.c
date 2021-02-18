#include <stdio.h>
#define SIZE 100

void read(int *array, int size)
{
    int i;
    for (i = 0; i < size; i++)
        scanf("%d", array + i);
    //scanf("%d", *array + i);
}

void swap(int *a, int *b)
{

    int temp = *a;
    *a = *b;
    *b = temp;
}

void print(const int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", *(array + i));
}

void sort(int *array, int *size)
{
    int *end = array + *size - 1, *i, *j;
    for (i = array; i != end; i++)
    {
        for (j = array; j != end; j++)
        {
            if (*j > *(j + 1))
            {

                swap(j, j + 1);
            }
        }
    }
}

int isSorted(const int array[], const int *size)
{
    int i;
    for (i = 0; i < *size - 1; i++)
        if (*(array + i) > *(array + i + 1))
            return 0;
    return 1;
}

int main()
{
    int arr[SIZE], len;
    scanf("%d", &len);
    read(arr, len);
    sort(arr, &len);
    printf("%s\n", isSorted(arr, &len) ? "All is good!" : "This isn't going as it's supposed to...");
    print(arr, len);
    return 0;
}
