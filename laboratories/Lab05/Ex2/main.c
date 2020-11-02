#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 20

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    if(in == NULL || out == NULL)
    {
        fprintf(stderr, "Error opening files.\n");
        exit(-1);
    }

    int r,c;
    fscanf(in, "%d %d", &r, &c);

    // Create and fill matrix
    char ***matrix = (char ***) malloc(r * sizeof(char **));
    for(int i = 0; i < r; ++i)
    {
        matrix[i] = (char **) malloc(c * sizeof(char *));
        for(int j = 0; j < c; ++j)
        {
            char buffer[MAX_STR_LEN + 1];
            fscanf(in, "%s", buffer);
            matrix[i][j] = strdup(buffer);
        }
    }

    char **result = (char **) malloc((r * c) * sizeof(char *));
    int *indexes = (int *) calloc(r, sizeof(int));

    // Sort into one array
    int index = 0;
    while(index < (r * c))
    {
        int row = 0;

        for(int i = 1; i < r; ++i)
            if(indexes[i] < c && strcmp(matrix[i][indexes[i]], matrix[row][indexes[row]]) < 0)
                row = i;

        result[index++] = matrix[row][indexes[row]++];
    }

    // Print output
    fprintf(out, "%d\n", (r * c));
    for(int i = 0; i < (r * c); ++i)
        fprintf(out, "%s\n", result[i]);

    // Free and close files
    for(int i = 0; i < r; ++i)
    {
        for(int j = 0; j < c; ++j)
            free(matrix[i][j]);

        free(matrix[i]);
    }

    free(matrix);
    free(indexes);
    free(result);

    fclose(in);
    fclose(out);

    return 0;
}