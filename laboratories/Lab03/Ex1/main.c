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
    char line[MAX_WORD_LEN + 1 + 1];

    while(fgets(line, (MAX_WORD_LEN + 1 + 1), wordFile) != NULL)
    {
        for(int i = 0; i < strlen(line); ++i)
            if(line[i] == '\n')
                line[i] = 0;
            else
                line[i] = tolower(line[i]);
        
        strncpy(words[index].word, line, (MAX_WORD_LEN + 1));
        words[index].frequency = 0;
        ++index;

        // At this point any eventual newline has already been replaced, so strlen(line) returns effective word length.
        if(strlen(line) > *maxWordLen)
            *maxWordLen = strlen(line);
    }

    return index;
}

void getFrequency(FILE *textFile, WORD *words, int wordCount)
{
    char line[MAX_LINE_LEN + 1 + 1];

    while(fgets(line, (MAX_LINE_LEN + 1 + 1), textFile) != NULL)
    {
        for(int i = 0; i < strlen(line); ++i)
            line[i] = tolower(line[i]);

        for(int i = 0; i < wordCount; ++i)
        {
            char *word = words[i].word;
            char *wpos = NULL;

            int wordLen = strlen(word);
            int frequency = 0;
            int offset = 0;

            do
            {
                wpos = strstr(line + offset, word);
                
                if(wpos != NULL)
                {
                    int j = wpos - line;

                    for(int k = j; k < wordLen; ++k)
                        line[k] = ' ';
                    
                    if((j == 0 || line[j-1] == ' ') && (line[j + wordLen] == 0 || line[j + wordLen] == ' ' || line[j + wordLen] == '\n'))
                    ++frequency;
                    offset = j + wordLen;
                }
            }
            while(wpos != NULL);

            words[i].frequency += frequency;
        }
    }
}