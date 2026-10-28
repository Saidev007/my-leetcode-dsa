int minCost(int** grid, int gridSize, int* gridColSize) {
    const int m = gridSize;
    const int n = gridColSize[0];

    bool (*dp)[1024] = calloc(n, sizeof(*dp));
    bool next[1024];

    dp[0][grid[0][0]] = true;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            const int value = grid[i][j];
            memset(next, 0, sizeof(next));

            for (int k = 0; k < 1024; k++) {
                if (dp[j][k] || (j > 0 && dp[j - 1][k])) {
                    next[k ^ value] = true;
                }
            }

            memcpy(dp[j], next, sizeof(next));
        }
    }

    int result = -1;

    for (int k = 0; k < 1024; k++) {
        if (dp[n - 1][k]) {
            result = k;
            break;
        }
    }

    free(dp);
    return result;
}
