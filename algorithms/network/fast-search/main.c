#include <stdio.h>
#include <string.h>

#define SIZE 50
#define TRUE 1

int getmaxnumlen(int num)
{
    int count = 1;

    while(num >= 10)
    {
        num -= (num % 10);
        num /= 10;
        ++count;
    }

    return count;
}

int main(void)
{
    int network[SIZE];
    int maxnumlen = 0;

    for(int i = 0; i < SIZE; ++i)
        network[i] = i;

    printf("Count: %d\n", (maxnumlen = getmaxnumlen(SIZE)));
    printf("Insert commands:\n");

    // Chars needed by both numbers + chars needed by command (query/union) + char needed for two spaces + null
    int p,q;
    char command[5+1];

    while(TRUE)
    {
        printf(">>> ");
        scanf("%s %d %d", command, &p, &q);

        if(!strcmp(command, "query"))
        {
            if(network[p] == network[q])
                printf("The two nodes are connected.\n");
            else
                printf("The two nodes are not connected.\n");
        }
        else if(!strcmp(command, "union"))
        {
            int value = network[p];
            for(int i = 0; i < SIZE; ++i)
                if(network[i] == value)
                    network[i] = network[q];
        }
        else
            printf("Invalid command.\n");
        
        for(int i = 0; i < SIZE; ++i)
            printf("%d ", network[i]);
        
        printf("\n");
    }
}