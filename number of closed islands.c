#include <stdbool.h>
#include <stdlib.h>

int bfs(int x, int y, int m, int n, int** grid, int* visited[]) {
    int q[m * n][2];
    int front = 0, rear = 0;
    int closed = 1;

    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    q[rear][0] = x;
    q[rear][1] = y;
    rear++;
    visited[x][y] = 1;

    while (front < rear) {
        x = q[front][0];
        y = q[front][1];
        front++;

        for (int i = 0; i < 4; i++) {
            int r = x + dx[i];
            int c = y + dy[i];

            if (r < 0 || r >= m || c < 0 || c >= n) {
                closed = 0;
            } else if (grid[r][c] == 0 && !visited[r][c]) {
                visited[r][c] = 1;
                q[rear][0] = r;
                q[rear][1] = c;
                rear++;
            }
        }
    }

    return closed;
}

int closedIsland(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int** visited = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        visited[i] = calloc(n, sizeof(int));
    }

    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                if (bfs(i, j, m, n, grid, visited)) {
                    count++;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        free(visited[i]);
    }
    free(visited);

    return count;
}
