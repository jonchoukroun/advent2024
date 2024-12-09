#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 128

int main(void)
{
    FILE* csv = fopen("./day2-input.csv", "r");
    if (csv == NULL) {
        printf("Failed to open file\n");
        return -1;
    }

    int safeCount = 0;
    char buffer[BUFF_SIZE] = {};
    while (fgets(buffer, BUFF_SIZE, csv)) {
        // Use sentinel values to track uninitialized
        int isAsc = -1;
        int lastLevel = -1;
        int isSafe = 1;
        for (char* token = strtok(buffer, ","); token; token = strtok(NULL, ",")) {
            int level;
            sscanf(token, "%d", &level);
            if (lastLevel < 0) {
                lastLevel = level;
                continue;
            }

            int diff = level - lastLevel;
            if (diff == 0 || diff > 3 || diff < -3) {
                isSafe = 0;
                break;
            }
            if (isAsc < 0) {
                isAsc = diff > 0 ? 1 : 0;
            }
            // Change in direction
            if ((diff > 0 && !isAsc) || (diff < 0 && isAsc)) {
                isSafe = 0;
                break;
            }

            lastLevel = level;
        }
        safeCount += isSafe;
        isSafe = 1;
    }

    if (fclose(csv) != 0) {
        printf("Failed to close file\n");
        return -1;
    }

    printf("Problem 1 = %d\n", safeCount);

    return 0;
}
