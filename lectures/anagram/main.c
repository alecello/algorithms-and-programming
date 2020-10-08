#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAXLENGTH 40

/*
 *  My implementation is slightly different from the reference one:
 * 
 *  In the reference implementation, the string lengths are not checked for equality.
 *  Instead, two (and not one) for loops are used to iterate over each string, each one by its respective length.
 * 
 *  I am not sure my solution is better, but I'm positive it's not worse, so I'm keeping it.
 */
int main(void)
{
    char frequencyDelta[26];

    char string1[MAXLENGTH];
    char string2[MAXLENGTH];
    
    printf("Insert first string (max %d characters): ", MAXLENGTH);
    scanf("%s", string1);

    printf("Insert second string (max %d characters): ", MAXLENGTH);
    scanf("%s", string2);

    int stringLength = (int) strlen(string1);

    if((int) strlen(string2) != stringLength)
    {
        printf("The strings are NOT anagrams (different length).\n");
        return 0;
    }

    for(int i = 0; i < 26; ++i)
    {
        frequencyDelta[i] = 0;
    }

    for(int i = 0; i < stringLength; ++i)
    {
        frequencyDelta[toupper(string1[i]) - 65]++;
        frequencyDelta[toupper(string2[i]) - 65]--;
    }

    int flag = 1;

    for(int i = 0; i < 26 && flag; ++i)
    {
        if(frequencyDelta[i])
        {
            flag = 0;
        }
    }

    if(flag)
        printf("The strings are anagrams.\n");
    else
        printf("The strings are NOT anagrams.\n");

    return 0;
}