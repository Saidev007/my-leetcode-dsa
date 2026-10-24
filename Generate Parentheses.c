#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve(int open, int close, int n, char *s,
           char **ans, int *count) {
    if (open == n && close == n) {
        ans[*count] = malloc(2 * n + 1);
        strcpy(ans[*count], s);
        (*count)++;
        return;
    }

    if (open < n) {
        s[open + close] = '(';
        solve(open + 1, close, n, s, ans, count);
    }

    if (close < open) {
        s[open + close] = ')';
        solve(open, close + 1, n, s, ans, count);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    char **ans = malloc(15000 * sizeof(char *));
    char *s = malloc(2 * n + 1);

    *returnSize = 0;
    s[2 * n] = '\0';

    solve(0, 0, n, s, ans, returnSize);

    free(s);
    return ans;
}
