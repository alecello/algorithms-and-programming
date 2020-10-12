#include <stdio.h>

#define LENGTH 10

int main(void)
{
    int array[LENGTH];

    for(int i = 0; i < LENGTH; ++i)
    {
        printf("array[%d]: ", i);
        scanf("%d", &array[i]);
    }

    int start = 0;
    int index = 0;
    int value = 0;
    int end = LENGTH;
    int position = -1;

    printf("Insert value to search: ");
    scanf("%d", &value);

    if(value < array[0] || value > array[LENGTH-1])
    {
        printf("Value out of range.\n");
        return 0;
    }

    do
    {
        index = (start + end)/2;

        if(array[index] == value)
        {
            position = index;
            break;
        }
        else if(array[index] < value)
        {
            start = ++index;
            continue;
        }
        else if(array[index] > value)
        {
            end = --index;
            continue;
        }
    }
    // At the last iteration, when value = end, if the value is not found we either ++start or --end, in both cases start > end
    // We can use this condition to exit the loop.
    while(start <= end);

    if(position == -1)
        printf("Value not found.\n");
    else
        printf("Value found at position %d.\n", position);
    
    return 0;
}