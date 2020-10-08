#include <stdio.h>

#define LENGTH 12

// Delete arbitrary values from array in most efficient way.
int main(void)
{
    int vector[12];
    int toDelete = 0;

    for(int i = 0 ; i < LENGTH; ++i)
    {
        printf("Insert vector[%d]: ", i);
        scanf("%d", &vector[i]);
    }

    printf("\nInsert value to delete: ");
    scanf("%d", &toDelete);

    int size = 0;
    for(int i = 0; i < LENGTH; ++i)
    {
        if(vector[i] != toDelete)
        {
            vector[size] = vector[i];
            ++size;
        }
    }

    printf("The array without the element \"%d\" is %d elements long.\n\n", toDelete, size);

    for(int i = 0; i < size; ++i)
    {
        printf("vector[%d]: %d\n", i, vector[i]);
    }

    return 0;
}