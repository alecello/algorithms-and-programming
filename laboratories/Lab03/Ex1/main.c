#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 19 // *SHORTER* than 20 characters.
#define MAX_LINE_LEN 99 // *SHORTER* than 100 characters.
#define MAX_WORD_NUM 100

typedef struct
{
    char word[MAX_WORD_LEN + 1];
    int frequency;
}
WORD;

int readWords(WORD *words, FILE *wordFile, int *maxWordLen);
void getFrequency(FILE *textFile, WORD *words, int wordCount);

int main(void)
{
    WORD words[MAX_WORD_NUM];

    int maxWordLen = 0;

    char *textFilePath = "text.txt";
    char *wordFilePath = "word.txt";

    FILE *textFile = fopen(textFilePath, "r");
    FILE *wordFile = fopen(wordFilePath, "r");

    if(textFile == NULL || wordFile == NULL)
    {
        printf("ERROR opening files.\n");
        return -1;
    }

    int wordCount = readWords(words, wordFile, &maxWordLen);
    getFrequency(textFile, words, wordCount);

    for(int i = 0; i < wordCount; ++i)
        if(words[i].frequency != 0)
            printf("%*s: %d\n", maxWordLen, words[i].word, words[i].frequency);
    
    fclose(wordFile);
    fclose(textFile);

    return 0;
}

int readWords(WORD *words, FILE *wordFile, int *maxWordLen)
{
    int index = 0;
    char WORD[MAX_WORD_LEN + 1];

    while(fscanf(wordFile, "%s", WORD) != EOF)
    {
        for(int i = 0; i < strlen(WORD); ++i)
            WORD[i] = tolower(WORD[i]);

        strncpy(words[index].word, WORD, (MAX_WORD_LEN + 1));
        words[index].frequency = 0;
        ++index;

        // At this point any eventual newline has already been replaced, so strlen(line) returns effective word length.
        if(strlen(WORD) > *maxWordLen)
            *maxWordLen = strlen(WORD);
    }

    return index;
}

void getFrequency(FILE *textFile, WORD *words, int wordCount)
{
    char WORD[MAX_LINE_LEN + 1];

    while(fscanf(textFile, "%s", WORD) != EOF)
    {
        for(int i = 0; i < strlen(WORD); ++i)
            WORD[i] = tolower(WORD[i]);
        
        for(int i = 0; i < wordCount; ++i)
            if(strlen(words[i].word) == strlen(WORD) && strcmp(words[i].word, WORD) == 0)
                ++words[i].frequency;
    }
}