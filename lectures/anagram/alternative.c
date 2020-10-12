#include <string.h>
#include <stdio.h>

#define MAXLENGTH 40

int main(void)
{
    char string1[MAXLENGTH + 1];
    char string2[MAXLENGTH + 1];
    
    printf("Insert first string (max %d characters): ", MAXLENGTH);
    scanf("%s", string1);

    printf("Insert second string (max %d characters): ", MAXLENGTH);
    scanf("%s", string2);

    int found, i, j;

    /*
     *  The usage of the found parameter is very elegant.
     * 
     *  It is set to true when entering the main check loop.
     *  On each character iteration, it is set to zero initially.
     *  If a match is found, the matched character gets substituted (to avoid duplicates) and found is set to true
     *  Setting it to true stops searching for a matching character in the second string as we already found one and lets the main loop continue.
     *  If a character is not found when we reach the end of the second string, the main loop exits.
     * 
     *  The flag also gets used to check wether we had a mismatching character (char in s1 not found in s2) to exit.
     * 
     *  In the second loop it gets set to false initially and switched to true if we find a character which has not been matched, in which case the program exits as the two strings are not anagrams (s2 longer than s1).
     * 
     *  Main takeaway: sometimes it is useful to declare variable outside of for, share/manipulate it across MULTIPLE fors and/or use it later as condition check.
     */
    for(found=1, i=0; i < strlen(string1) && found; ++i)
        for(found=0, j=0; j < strlen(string2) && !found; j++)
            if(string2[j] == string1[i])
            {
                string2[j] = '-';
                found = 1;
            }
    
    if(!found)
    {
        printf("NOT anagrams.\n");
        return 0;
    }
    else
    {
        for(found=0, i=0; i < strlen(string2) && !found; ++i)
            if(string2[i] != '-')
                found = 1;
        
        if(!found)
            printf("YES anagrams.\n");
        else
            printf("NOT anagrams.\n");
    }
    
}