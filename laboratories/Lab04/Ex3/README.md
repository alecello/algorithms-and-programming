### Notes
The program uses static array allocation for each atlethe's name inside the structure:

``` C
typedef struct
{
    char name[MAX_NAME + 1];

    /* ... */
}
CYCLIST;
```

However, the official solution uses dynamic memory allocation and replaces `char name[MAX_NAME] + 1` with `char *name`.

Since the exercise's text did not specify to use dynamic memory allocation for that, I am not correcting the exercise or considering it as incomplete.