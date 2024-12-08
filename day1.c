#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int problem1(int* arrA, int* arrB, int arrSize);
int problem2(int* arrA, int* arrB, int arrSize);

int main(void)
{
    FILE* csv = fopen("./day1-a-input.csv", "r");
    if (csv == NULL) {
        printf("Failed to open csv\n");
        return -1;
    }

    // Bring the input from a CSV into 2 separate arrays
    int arrSize = 1000;
    int arrA[arrSize];
    int arrB[arrSize];

    int bufSize = 1024;
    char buffer[bufSize];
    int i = 0;
    while (fgets(buffer, bufSize, csv)) {
        char* a = strtok(buffer, ",");
        char* b = strtok(NULL, ",");

        int iA;
        int iB;
        sscanf(a, "%d", &iA);
        sscanf(b, "%d", &iB);

        arrA[i] = iA;
        arrB[i] = iB;

        i++;
    }

    printf("Problem 1 = %d\n", problem1(arrA, arrB, arrSize));
    // problem2 won't execute correctly if problem1 doesn't run first to sort arrays
    printf("Problem 2 = %d\n", problem2(arrA, arrB, arrSize));

    return 0;
}

int problem1(int* arrA, int* arrB, int arrSize)
{
    // Sorting the arrays in place allows for optimizing problem 2
    qsort(arrA, arrSize, sizeof(int), &cmp);
    qsort(arrB, arrSize, sizeof(int), &cmp);

    int sum = 0;
    for (int i = 0; i < 1000; ++i) {
        if (arrA[i] > arrB[i]) {
            sum += arrA[i] - arrB[i];
        } else {
            sum += arrB[i] - arrA[i];
        }
    }

    return sum;
}

int problem2(int* arrA, int* arrB, int arrSize)
{
    int sum = 0;
    // Track the start of a set of duplicates
    int startPos = 0;
    // Step through dups
    int cursor = 0;
    for (int i = 0; i < arrSize; ++i) {
        int count = 0;
        while (cursor < arrSize && arrB[cursor] <= arrA[i]) {
            if (arrB[cursor] == arrA[i]) {
                count++;
            }
            cursor++;
        }
        sum += arrA[i] * count;
        // Lookahead to bump startPos if next arrA is greater than current
        if (arrA[i + 1] > arrA[i]) {
            // Don't need to keep iterating if cursor reaches max and rest of arrA aren't dups
            if (cursor >= arrSize) {
                return sum;
            }
            startPos = cursor;
        } else {
            cursor = startPos;
        }
    }

    return sum;
}
