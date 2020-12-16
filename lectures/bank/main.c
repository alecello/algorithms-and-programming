#include <stdio.h>

#define N 4

#define MIN(x, y) (x > y) ? y : x
#define MAX(x, y) (x < y) ? y : x

void solve(int count, float *movements, int *available, int *bestcombo, int *currcombo, float *record, float minimum, float maximum, float balance);

int main(void)
{
    float movements[N];
    int  available[N];
    int  bestcombo[N];
    int  currcombo[N];

    for(int i = 0; i < N; ++i)
    {
        printf("Insert value #%d: ", (i +1));
        scanf("%f", &movements[i]);

        available[i] = 1;
        bestcombo[i] = 0;
    }

    float record = -1.0f;
    solve(0, movements, available, bestcombo, currcombo, &record, 0, 0, 0);

    printf("\n");
    for(int i = 0; i < N; ++i)
        printf("Movement #%d: %+02.2f\n", (i + 1), movements[bestcombo[i]]);

    return 0;
}

float min(float a, float b)
{
    if(a < b) return a; else return b;
}

float max(float a, float b)
{
    if(a > b) return a; else return b;
}

void solve(int count, float *movements, int *available, int *bestcombo, int *currcombo, float *record, float minimum, float maximum, float balance)
{
    // The score can only get worse: If we're already worse off than the previous record (and a previous record exists) just give up
    if(*record >= 0 && (maximum - minimum) > *record)
        return;

    if(count == N)
    {
        printf("\n\tScore: %2.2f (min: %+02.2f, max: %+02.2f)\n\t\t", (maximum - minimum), minimum, maximum);
        for(int i = 0; i < N; ++i)
            printf("%+02.2f ", movements[currcombo[i]]);
        printf("\n");

        if(*record == -1.0f || (maximum - minimum) < *record)
        {
            *record = (maximum - minimum);

            for(int i = 0; i < N; ++i)
                bestcombo[i] = currcombo[i];
        }

        return;
    }

    for(int i = 0; i < N; ++i)
    {
        if(available[i] != 1)
            continue;

        available[i] = 0;
        currcombo[count] = i;

        float newMinimum = min(minimum, balance + movements[i]);
        float newMaximum = max(maximum, balance + movements[i]);

        solve((count + 1), movements, available, bestcombo, currcombo, record, newMinimum, newMaximum, (balance + movements[i]));
        available[i] = 1;
    }
}
