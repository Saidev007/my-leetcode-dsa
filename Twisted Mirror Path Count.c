#include <stdlib.h>
#include <stdint.h>

#define MOD 1000000007

int uniquePaths(int** grid, int gridSize, int* gridColSize) {
    const int MOD = 1000000007;
    int m = gridSize;
    int n = gridColSize[0];

    // Dynamically allocate the two-dimensional array f[n][2]
    int64_t** f = (int64_t**)malloc(n * sizeof(int64_t*));
    for (int j = 0; j < n; j++) {
        f[j] = (int64_t*)calloc(2, sizeof(int64_t));
    }
    f[0][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) {
                if (grid[i - 1][j] == 0) {
                    f[j][0] = (f[j][0] + f[j][1]) % MOD;
                } else {
                    f[j][0] = f[j][1];
                }
            }

            if (j > 0) {
                if (grid[i][j - 1] == 0) {
                    f[j][1] = (f[j - 1][0] + f[j - 1][1]) % MOD;
                } else {
                    f[j][1] = f[j - 1][0];
                }
            }
        }
    }

    int result = (int)((f[n - 1][0] + f[n - 1][1]) % MOD);
    for (int j = 0; j < n; j++) {
        free(f[j]);
    }
    free(f);

    return result;
}
