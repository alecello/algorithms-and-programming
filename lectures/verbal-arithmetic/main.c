#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MLEN  8
#define MNUM 10

int put(char c, char *array, int len);
int solve(int level, int count, char *letters, char *numbers, char *deleted, char *w1, char *w2, char *w3);
int check(char *letters, char *numbers, int count, char *w1, char *w2, char *w3);
int convert(char *string, char *letters, char *numbers, int count);
int lookup(char c, char *letters, char *numbers, int count);
int power(int base, int exponent);

int counter = 0;

int main(void)
{
    char word1[MLEN + 1];
    char word2[MLEN + 1];
    char word3[MLEN + 1];

    char letters[MNUM];
    char numbers[MNUM];
    char deleted[MNUM];

    int count = 0;

    // Initialize
    for(int i = 0; i < MNUM; ++i)
    {
        letters[i] = -1;
        numbers[i] = -1;
        deleted[i] =  0;

        word1[i]= 0;
        word2[i]= 0;
        word3[i]= 0;
    }

    printf("Performing A + B = C\n");
    
    printf("\tA = ");
    scanf("%s", word1);
    
    printf("\tB = ");
    scanf("%s", word2);
    
    printf("\tC = ");
    scanf("%s", word3);

    // Put all letters inside the array
    for(int i = 0; i < MLEN; ++i)
    {
        count = put(word1[i], letters, count);
        count = put(word2[i], letters, count);
        count = put(word3[i], letters, count);
    }

    char choice;
    printf("\nDo you want to check your solution? [y/N]: ");
    scanf(" %c", &choice);

    if(tolower(choice) == 'y')
    {
        for(int i = 0; i < count; ++i)
        {
            int input = -1;

            do
            {
                printf("\t%c == ", letters[i]);
                scanf(" %d", &input);

                // Flush any invalid/incomplete input
                while(fgetc(stdin) != '\n');
            }
            while(input < 0 || input > 9);

            numbers[i] = input;
        }

        if(check(letters, numbers, count, word1,word2, word3))
            printf("\nThis is a valid solution!\n");
        else
            printf("\nThis is not a solution!\n");
    }
    else
    {
        putchar('\n');
        if(solve(0, count, letters, numbers, deleted, word1, word2, word3))
            for(int i = 0; i < count; ++i)
                printf("%c == %d\n", letters[i], numbers[i]);
        else
            printf("\nNo solution found!\n");    
    }

    return 0;
}

int put(char c, char *array, int len)
{
    // Skip non-letters
    if(!isalpha(c))
        return len;

    for(int i = 0; i < len; ++i)
        if(array[i] == c)
            return len;
    
    array[len++] = c;
    return len;
}

int solve(int level, int count, char *letters, char *numbers, char *deleted, char *w1, char *w2, char *w3)
{
    // Array of MSDs (Most Significant Digits)
    char MSDigits[3] = {w1[0], w2[0], w3[0]};

    counter++;
    if(level == count)
        return check(letters, numbers, count, w1, w2, w3);
    
    for(int i = 0; i < MNUM; ++i)
    {
        // Do not put a MSD (Most Significant Digit) to zero since it's forbidden
        if((i == 0) && (letters[level] == MSDigits[0] || letters[level] == MSDigits[1] || letters[level] == MSDigits[2]))
            continue;

        if(!deleted[i])
        {
            deleted[i] = 1;
            numbers[level] = i;

            if(solve((level + 1), count, letters, numbers, deleted, w1, w2, w3))
                return 1;
            else
                deleted[i] = 0;
        }
    }

    return 0;
}

int check(char *letters, char *numbers, int count, char *w1, char *w2, char *w3)
{
    // Most significant digit must not be zero
    // This check is redundant during *solution* of a problem but not during validation of the user's solution
    // Additional conditions might be used to only execute this in that specific case, but it's not a big performance hit
    if(!lookup(w1[0], letters, numbers, count) || !lookup(w2[0], letters, numbers, count) || !lookup(w3[0], letters, numbers, count))
        return 0;

    int num1 = convert(w1, letters, numbers, count);
    int num2 = convert(w2, letters, numbers, count);
    int num3 = convert(w3, letters, numbers, count);

    return((num1 + num2) == num3);
}

int convert(char *string, char *letters, char *numbers, int count)
{
    int len = strlen(string);
    int sum = 0;

    for(int i = (len - 1); i >= 0; --i)
    {
        int digit = lookup(string[i], letters, numbers, count);
        sum += power(10, (len - i - 1)) * digit;
    }

    return sum;
}

int lookup(char c, char *letters, char *numbers, int count)
{
    for(int i = 0; i < count; ++i)
        if(letters[i] == c)
            return numbers[i];
    
    return 0;
}

int power(int base, int exponent)
{
    if(exponent == 0)
        return 1;

    int sum = base;

    for(int i = 1; i < exponent; ++i)
        sum *= base;
    
    return sum;
}