#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    int len = strlen(s);

    char* result = malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    if (numRows <= 1 || numRows >= len) {
        strcpy(result, s);
        return result;
    }

    int cycle = 2 * numRows - 2;
    int k = 0;

    for (int row = 0; row < numRows; row++) {
        for (int j = 0; j + row < len; j += cycle) {
            result[k++] = s[j + row];

            int diagonal = j + cycle - row;

            if (row != 0 &&
                row != numRows - 1 &&
                diagonal < len) {
                result[k++] = s[diagonal];
            }
        }
    }

    result[k] = '\0';
    return result;
}
