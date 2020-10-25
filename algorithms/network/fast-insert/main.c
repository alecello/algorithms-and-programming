#include <stdio.h>

#define SIZE 10

int findParentNode(int node, int *network);

int main(void)
{
    int network[SIZE];

    for(int i = 0; i < SIZE; ++i)
        network[i] = i;

    char verb;
    int p;
    int q;

    printf("Waiting for instructions.\nTo test a connection: t <node1> <node2>\nTo make a connection: m <node1> <node2>\nTo print the network: p\n\n");
    while(scanf(" %c", &verb) != EOF)
    {
        if(verb == 'p')
        {
            printf("\n|");
            for(int i = 0; i < SIZE; ++i)
                printf("%2d|", i);
            
            printf("\n-");
            for(int i = 0; i < SIZE; ++i)
                printf("---");
            
            printf("\n|");
            for(int i = 0; i < SIZE; ++i)
                printf("%2d|", network[i]);
            
            printf("\n\n");
            continue;
        }
        
        scanf("%d %d", &p, &q);

        int parent1 = findParentNode(p, network);
        int parent2 = findParentNode(q, network);
        
        if(verb == 'm')
            network[parent1] = parent2;
        else if(verb == 't')
            if(parent1 == parent2)
                printf("The nodes are connected.\n");
            else
                printf("The nodes are disconnected.\n");
        else
            printf("Invalid command.\n");
    }

    return 0;
}

int findParentNode(int node, int *network)
{
    int index = node;
    int value = node;

    while((value = network[index]) != index)
        index = value;
    
    return index;
}