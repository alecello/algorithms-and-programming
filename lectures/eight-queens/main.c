#include <stdio.h>

#define SIZE 8

int placeQueens(char chessboard[SIZE][SIZE], int n);
int placeQueen(char chessboard[SIZE][SIZE], int current, int max);
void writeReach(char chessboard[SIZE][SIZE], int r, int c, char val);
void printBoard(char chessboard[SIZE][SIZE], int prettyPrint);

int main(void)
{
    char chessboard[SIZE][SIZE];

    for(int r = 0; r < SIZE; ++r)
        for(int c = 0; c < SIZE; ++c)
            chessboard[r][c] = 0;

    int result = placeQueens(chessboard, 8);

    if(result)
        printBoard(chessboard, 1);
    else
        printf("Error: unable to solve the problem.\n");
}

int placeQueens(char chessboard[SIZE][SIZE], int n)
{
    if(placeQueen(chessboard, 0, n))
        return 1;
    
    return 0;
}

int placeQueen(char chessboard[SIZE][SIZE], int current, int max)
{
    if(current == max)
        return 1;

    for(int r = 0; r < SIZE; ++r)
        for(int c = 0; c < SIZE; ++c)
            if(chessboard[r][c] == 0)
            {                
                chessboard[r][c] = -1;
                writeReach(chessboard, r, c, 1);

                if(placeQueen(chessboard, (current + 1), max))
                    return 1;
                else
                {
                    writeReach(chessboard, r, c, -1);
                    chessboard[r][c] = 0;
                }
            }
    
    return 0;
}

void writeReach(char chessboard[SIZE][SIZE], int r, int c, char val)
{
    char flag = 1;
    int k = 1;

    while(flag)
    {
        flag = 0;
        
        if((r - k) >= 0)
        {
            chessboard[r-k][c] += val;

            if((c - k) >= 0)
                chessboard[r-k][c-k] += val;

            if((c + k) < SIZE)
                chessboard[r-k][c+k] += val;
            
            flag = 1;
        }
        
        if((r + k) < SIZE)
        {
            chessboard[r+k][c] += val;

            if((c - k) >= 0)
                chessboard[r+k][c-k] += val;

            if((c + k) < SIZE)
                chessboard[r+k][c+k] += val;
            
            flag = 1;
        }

        if((c - k) >= 0)
        {
            chessboard[r][c-k] += val;
            flag = 1;
        }

        if((c + k) < SIZE)
        {
            chessboard[r][c+k] += val;
            flag = 1;
        }

        ++k;
    }
}

void printBoard(char chessboard[SIZE][SIZE], int prettyPrint)
{
    for(int r = 0; r < SIZE; ++r)
    {
        for(int c = 0; c < SIZE; ++c)
            if(chessboard[r][c] == -1)
                putchar('Q');
            else if(chessboard[r][c] != 0 && prettyPrint)
                putchar('-');
            else
                putchar('0' + chessboard[r][c]);
        
        putchar('\n');
    }
}