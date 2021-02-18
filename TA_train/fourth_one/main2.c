#include <stdio.h>
#include <float.h>

int main()
{
    int n;
    float sum = 0, max = -FLT_MAX, min = FLT_MAX, temp;
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%f", &temp);
        max = (temp > max) ? temp : max;
        min = (temp < min) ? temp : min;
        sum += temp;
    }
    printf("Max: %.3f\n", max);
    printf("Min: %.3f\n", min);
    printf("Avg: %.3f\n", sum / n);
}