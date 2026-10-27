#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int left;
    int right;
} Seg;

int cmp(const void* a, const void* b) {
    Seg* x = (Seg*)a;
    Seg* y = (Seg*)b;

    if (x->right == y->right) {
        return y->left - x->left;
    }

    return x->right - y->right;
}

char** maxNumOfSubstrings(char* s, int* returnSize) {
    Seg seg[26];

    for (int i = 0; i < 26; i++) {
        seg[i].left = -1;
        seg[i].right = -1;
    }

    int n = strlen(s);

    for (int i = 0; i < n; i++) {
        int charIdx = s[i] - 'a';

        if (seg[charIdx].left == -1) {
            seg[charIdx].left = seg[charIdx].right = i;
        } else {
            seg[charIdx].right = i;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (seg[i].left != -1) {
            int j = seg[i].left;

            while (j <= seg[i].right) {
                int charIdx = s[j] - 'a';

                if (seg[i].left <= seg[charIdx].left &&
                    seg[charIdx].right <= seg[i].right) {
                } else {
                    if (seg[charIdx].left < seg[i].left) {
                        seg[i].left = seg[charIdx].left;
                    }

                    if (seg[charIdx].right > seg[i].right) {
                        seg[i].right = seg[charIdx].right;
                    }

                    j = seg[i].left;
                }

                j++;
            }
        }
    }

    qsort(seg, 26, sizeof(Seg), cmp);

    char** ans = (char**)malloc(sizeof(char*) * 26);
    *returnSize = 0;

    int end = -1;

    for (int i = 0; i < 26; i++) {
        int left = seg[i].left;
        int right = seg[i].right;

        if (left == -1) {
            continue;
        }

        if (end == -1 || left > end) {
            end = right;

            int len = right - left + 1;
            ans[*returnSize] = (char*)malloc(len + 1);

            strncpy(ans[*returnSize], s + left, len);
            ans[*returnSize][len] = '\0';

            (*returnSize)++;
        }
    }

    return ans;
}
