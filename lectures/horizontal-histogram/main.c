#include <stdio.h>

#define RANGE 99
#define DIVISION 10

int main(void)
{
    int values[DIVISION];
    int input =  100;

    // Initialize array
    for(int i = 0; i < DIVISION; ++i)
    {
        values[i] = 0;
    }

    while(1)
    {
        printf(">>> ");
        scanf("%d", &input);

        if(input < 0 || input > RANGE)
            break;

        values[input / DIVISION]++;
    }

    printf("\n\n");

    for(int i = 0; i < DIVISION; ++i)
    {
        printf("%2d - %2d ", DIVISION * (i), (DIVISION * (i+1)) - 1);

        for(int j = 0; j < values[i]; ++j)
            printf("#");

        printf("\n");
    }
}