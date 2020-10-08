#include <stdio.h>

/*
 *  Simple code snippet shown in in-class to demonstrate how string passing between functions work
 *  
 *  NOTE: Not written by me! This code has been copy-pasted from Prof. G. Politano's slides.
 *        I only added the two "Press enter to continue..." messages
 */
int slen(char *);

int main(void) {
    char s[500];
    printf("%s","Enter a sentence: ");

    if(!fgets(s, 500, stdin)) {
        puts("Error!");
        puts("Press enter to continue...");
        getchar();
        return 0;
    }

    for(int i=0; i<slen(s);i++)
        if(s[i]!=32)
            putchar(s[i]);
        else
            putchar(10);
    putchar(10);
    puts("Press enter to continue...");
    getchar();
    return 0;
}

int slen(char *s) {
    int i;
    for(i=0;s[i]!=0;i++);
    return i;
}