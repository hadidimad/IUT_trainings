#include <stdio.h>
void bubbleSort(int *array, int length)
{
    int temp;
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int input[3];
    char order[3];
    scanf("%i %i %i", &input[0], &input[1], &input[2]);
    scanf("%s", order);
    bubbleSort(input, 3);
    for (int i = 0; i < 3; i++)
    {
        switch (order[i])
        {
        case 'A':
            printf("%i ", input[0]);
            break;
        case 'B':
            printf("%i ", input[1]);
            break;
        case 'C':
            printf("%i ", input[2]);
            break;
        }
    }

    return 0;
}