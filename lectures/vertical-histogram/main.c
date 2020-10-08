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
        scanf("%d", &input);

        if(input < 0 || input > RANGE)
            break;

        values[input / DIVISION]++;
    }

    printf("\n\n");

    int max = 0;
    for(int i = 0; i < DIVISION; ++i)
    {
        if(values[i] > max)
            max = values[i];
    }

    int flag = 0;
    do
    {
        flag = 0;

        for(int j = 0; j < DIVISION; ++j)
        {
            if(values[j] > 0)
            {
                printf("#");

                values[j]--;
                flag = 1;
            }
            else
                printf(" ");
        }

        printf("\n");
    }
    while(flag);
}