#include <stdio.h>
#include <ctype.h>

#define LENGTH 10   // Length of the array
#define TRUE 1
#define FALSE 0

int main(void)
{
    int array[LENGTH];
    int ordered = FALSE;
    int value;

    char answer;

    for(int i = 0; i < LENGTH; ++i)
    {
        printf("array[%d]: ", i);
        scanf("%d", &array[i]);
    }

    // If the array is ordered, we can stop before reaching the end if array[i] > value
    printf("Is the array ordered? y/N: ");
    scanf("\n%c", &answer);
    answer = tolower(answer);

    if(answer == 'y')
        ordered = TRUE;

    printf("Insert the value to search for: ");
    scanf("%d", &value);

    for(int i = 0; i < LENGTH; ++i)
        if(array[i] == value)
        {
            printf("Value found at index %d.\n", i);
            return 0;
        }
        else if(ordered && array[i] > value)
            break;

    printf("Value not found.\n");
    return 1;
}