#include <stdio.h>
#include <ctype.h>
#include <string.h>

int mult(int a, int b)
{
    if(b == 0)
        return 0;
    if(b == 1)
        return a;
    else
        return a + mult(a, b-1);
        // a + (a + (a + (a + (...))))
}

void d2b(int d, int *b, int *n)
{
    if(d < 2)
    {
        b[(*n)++] = d;
        return;
    }

    b[(*n)++] = d % 2;
    d /= 2;
    
    d2b(d, b, n);
}

int catalan(int n)
{
    if(n == 0)
        return 1;
    
    int result = 0;

    for(int i = 0; i < n; ++i)
        result += catalan(i) * catalan(n - 1 - i);
    
    return result;
}

int countSpaces(char *s)
{
    if(strlen(s) == 1)
        return isspace(s[0]);
    
    return (isspace(s[0]) ? 1 : 0) + countSpaces(&s[1]);
}

int isPalindrome(char *s, int l)
{
    if(l == 1)
        return 1;
    else if(l == 2)
        return s[0] == s[1];
    
    return (s[0] == s[l-1] && isPalindrome(&s[1], l-2));
}

void triangle_r(int r, int max)
{
    if(r > max)
        return;
    
    for(int i = 0; i < r; ++i)
        putchar('0' + r);
    
    putchar('\n');
    triangle_r(r + 1, max);
}

void triangle_r_norecurse(int r, int c, int max)
{
    if(r > max)
        return;

    if(c > r)
    {
        c = 1;
        ++r;

        putchar('\n');
    }

    putchar('0'+ r);
    triangle_r_norecurse(r, c+1, max);
}

// Wrapper for triangle_r
void triangle(int n)
{
    triangle_r(1, n);
}

// Wrapper for triangle_r_norecurse
void triangle_norecurse(int n)
{
    triangle_r_norecurse(1, 1, n);
}

int main(void)
{
    // Enough for any int input
    int b[64];
    int n = 0;

    char *s = "This is a string with spaces!";

    printf("RECURSIVE MULTIPLICATION OF 3 * 10 = %d\n", mult(3, 10));
    printf("\nBINARY FORM OF 23 = ");
    d2b(23, b, &n);

    for(int i = (n-1); i >= 0; --i)
        printf("%d", b[i]);
    
    putchar('\n');

    n = 0;
    printf("\nBINARY FORM OF 24 = ");
    d2b(24, b, &n);

    for(int i = (n-1); i >= 0; --i)
        printf("%d", b[i]);
    
    putchar('\n');

    printf("\nFIRST TEN CATALAN NUMBERS:\n");

    for(int i = 0; i < 10; ++i)
        printf("\t%d\n", catalan(i));
    
    printf("\nTHE STRING \"%s\" HAS %d SPCACES\n", s, countSpaces(s));
    printf("\nTHE NUMBER %d IS %s", 12321, isPalindrome("12321", 5) ? "PALINDROME" : "NOT PALINDROME");
    printf("\nTHE NUMBER %d IS %s", 12345, isPalindrome("12345", 5) ? "PALINDROME" : "NOT PALINDROME");
    printf("\nHAVE A NICE TRIANGLE:\n\n");

    triangle(9);

    printf("\nHAVE A NICE RECURSION-FREE TRIANGLE:\n\n");

    triangle_norecurse(9);
}