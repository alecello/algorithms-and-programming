#include <stdio.h>

/*
 *  Simple code snippet shown in in-class to demonstrate how string passing between functions work
 *  
 *  NOTE: Not written by me! This code has been copy-pasted from Prof. G. Politano's slides.
 *        I only added a newline to the last printf, removed the static prefix to roman_to_integer and omitted including stdlib
 */
int roman_to_integer(char c) {
    switch(c) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
    }
}

int roman_to_int(char *s) {
    int i, int_num = roman_to_integer(s[0]);

    for(i = 1; s[i] != '\0'; i++) {
        int prev_num = roman_to_integer(s[i - 1]);
        int cur_num = roman_to_integer(s[i]);
        if(prev_num < cur_num) {
            int_num = int_num - prev_num + (cur_num - prev_num);
        } else {
            int_num += cur_num;
        }
    }
    return int_num;
}

int main(void) {
    char *str1 = "XIV";
    printf("Original roman number: %s", str1);
    printf("\nRoman to integer: %d\n", roman_to_int(str1));
    return 0;
}