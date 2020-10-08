#include <stdio.h>

#define DIM1 5
#define DIM2 3

// Set to 1 to allow detection of overlapping occurrences.
#define OVERLAPPING 0


// Find a subvector using the sliding window algorithm.
int main(void)
{
    int v1[DIM1];
    int v2[DIM2];

    for(int i = 0; i < DIM1; ++i)
    {
        printf("Insert value %d of the big vector: ", i+1);
        scanf("%d", &v1[i]);
    }

    printf("\n");

    for(int i = 0; i < DIM2; ++i)
    {
        printf("Insert value %d of the small vector: ", i+1);
        scanf("%d", &v2[i]);
    }

    int i = 0;
    while(i <= (DIM1 - DIM2))
    {
        int found = 1;

        if(v1[i] == v2[0])
        {
            int j = 1;

            while(j < DIM2 && found)
            {
                if(v2[j] != v1[i+j])
                    found = 0;

                ++j;
            }

            if(found)
                printf("Subvector found at pos %d.\n", i);          
        }
        else
            found = 0;

        i += (!OVERLAPPING && found) ? DIM2 : 1;  
    }
}