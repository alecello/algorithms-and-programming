#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x1;
    int y1;
    int connected1;

    int x2;
    int y2;
    int connected2;
}
LINE;

int getConnections(LINE *data, int dataCount, int line, int extreme);

int main(void)
{
    int linesNumber;
    LINE *vector;

    FILE *inputFile = fopen("input.txt", "r");
    if(inputFile == NULL)
    {
        fprintf(stderr, "Error while opening file.\n");
        return -1;
    }

    fscanf(inputFile, "%d\n", &linesNumber);
    vector = (LINE *) calloc(linesNumber, sizeof(LINE));

    for(int i = 0; i < linesNumber; ++i)
    {
        int x1,y1,x2,y2;
        fscanf(inputFile, "%d %d %d %d\n", &x1, &y1, &x2, &y2);

        vector[i].x1 = x1;
        vector[i].y1 = y1;
        vector[i].x2 = x2;
        vector[i].y2 = y2;

        vector[i].connected1 = 0;
        vector[i].connected2 = 0;
    }

    int disconnectedEnds = 0;   // Both ends disconnected
    int overconnectedEnds = 0;  // At least one end is connected to more than one line

    for(int i = 0; i < linesNumber; ++i)
    {
        for(int j = (i + 1); j < linesNumber; ++j)
        {
            if(vector[i].x1 == vector[j].x1 && vector[i].y1 == vector[j].y1)
            {
                ++vector[i].connected1;
                ++vector[j].connected1;
            }
            if(vector[i].x1 == vector[j].x2 && vector[i].y1 == vector[j].y2)
            {
                ++vector[i].connected1;
                ++vector[j].connected2;
            }
            if(vector[i].x2 == vector[j].x1 && vector[i].y2 == vector[j].y1)
            {
                ++vector[i].connected2;
                ++vector[j].connected1;
            }
            if(vector[i].x2 == vector[j].x2 && vector[i].y2 == vector[j].y2)
            {
                ++vector[i].connected2;
                ++vector[j].connected2;
            }
        }

        char *status1 = "OK";
        char *status2 = "OK";

        if(vector[i].connected1 == 0)
        {
            ++disconnectedEnds;
            status1 = "Disconnected";
        }
        else if(vector[i].connected1 > 1)
        {
            ++overconnectedEnds;
            status1 = "Invalid";
        }

        if(vector[i].connected2 == 0)
        {
            ++disconnectedEnds;
            status2 = "Disconnected";
        }
        else if(vector[i].connected2 > 1)
        {
            ++overconnectedEnds;
            status2 = "Invalid";
        }

        printf("Segment %2d %2d %2d %2d - left: %-12s ; right: %-12s\n", vector[i].x1, vector[i].y1, vector[i].x2, vector[i].y2, status1, status2);
    }

    if(disconnectedEnds && overconnectedEnds != 0)
        printf("Multiple broken lines, at least one invalid.\n");
    else if(disconnectedEnds > 2 && overconnectedEnds == 0)
        printf("Broken line with disconnected segments.\n");
    else if(disconnectedEnds <= 2 && overconnectedEnds == 0)
        printf("Single broken line.\n");


    fclose(inputFile);
    free(vector);

    return 0;
}

int getConnections(LINE *data, int dataCount, int line, int extreme)
{
    int x,y;
    int connections = 0;

    if(extreme == 1)
    {
        x = data[line].x1;
        y = data[line].y1;
    }
    else
    {
        x = data[line].x2;
        y = data[line].y2;
    }
    
    for(int i = 0; i < dataCount; ++i)
        if(i != line && ((data[i].x1 == x && data[i].y1 == y) || (data[i].x2 == x && data[i].y2 == y)))
            ++connections;
    
    return connections;
}