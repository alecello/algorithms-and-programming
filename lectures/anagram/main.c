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

    /*
     *  ALTERNATIVE IMPLEMENTATION TAKEN FROM LECTURE
     *  =============================================
     * 
     * 
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

    /*
     *  int found,i,j;
     *
     *  for(found=1, i=0; i < strlen(string1) && found; ++i)
     *      for(found=0, j=0; j < strlen(string2) && !found; j++)
     *          if(string2[j] == string1[i])
     *          {
     *              string2[j] = '-';
     *              found = 1;
     *          }
     *  
     *  if(!found)
     *  {
     *      printf("NOT anagrams.\n");
     *      return 0;
     *  }
     *  else
     *  {
     *      for(found=0, i=0; i < strlen(string2) && !found; ++i)
     *          if(string2[i] != '-')
     *              found = 1;
     *      
     *      if(!found)
     *          printf("YES anagrams.\n");
     *      else
     *          printf("NOT anagrams.\n");
     *  }
     */
}