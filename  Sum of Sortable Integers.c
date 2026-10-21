int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int kmp(int* nums1, int n, int* nums2, int m) {
    int* pi = (int*)calloc(m, sizeof(int));
    int j = 0;

    for (int i = 1; i < m; i++) {
        while (j > 0 && nums2[i] != nums2[j]) {
            j = pi[j - 1];
        }
        if (nums2[i] == nums2[j]) {
            j++;
        }
        pi[i] = j;
    }

    j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && nums1[i] != nums2[j]) {
            j = pi[j - 1];
        }
        if (nums1[i] == nums2[j]) {
            j++;
        }
        if (j == m) {
            free(pi);
            return 1;
        }
    }
    free(pi);
    return 0;
}

int check(int* nums1, int len, int* nums2) {
    // Check whether cyclic rotations of nums1 can produce nums2
    int* doubled = (int*)malloc(2 * len * sizeof(int));
    memcpy(doubled, nums1, len * sizeof(int));
    memcpy(doubled + len, nums1, len * sizeof(int));
    int result = kmp(doubled, 2 * len, nums2, len);
    free(doubled);
    return result;
}

int sortableIntegers(int* nums, int numsSize) {
    int n = numsSize;
    int* fac = (int*)malloc(n * sizeof(int));
    int facCount = 0;

    for (int x = 1; x * x <= n; x++) {
        if (n % x == 0) {
            fac[facCount++] = x;
            if (n / x != x) {
                fac[facCount++] = n / x;
            }
        }
    }

    int* target = (int*)malloc(n * sizeof(int));
    memcpy(target, nums, n * sizeof(int));
    qsort(target, n, sizeof(int), compare);

    int ans = 0;

    for (int i = 0; i < facCount; i++) {
        int d = fac[i];
        int allGood = 1;

        for (int left = 0; left < n; left += d) {
            if (!check(nums + left, d, target + left)) {
                allGood = 0;
                break;
            }
        }

        if (allGood) {
            ans += d;
        }
    }

    free(fac);
    free(target);
    return ans;
}