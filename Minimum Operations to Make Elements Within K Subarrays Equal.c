#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    bool isMax;
} MedianHeap;

typedef struct {
    int key;
    int count;
    bool used;
} DelayedEntry;

typedef struct {
    MedianHeap left, right;
    DelayedEntry* delayed;
    int delayedCapacity;
    int leftSize, rightSize;
    long long sumL, sumR;
} DualHeap;

static unsigned int delayedHash(int key) {
    uint32_t value = (uint32_t)key;
    value ^= value >> 16;
    value *= 0x7feb352dU;
    value ^= value >> 15;
    value *= 0x846ca68bU;
    value ^= value >> 16;
    return value;
}

static DelayedEntry* findDelayed(DualHeap* heaps, int key, bool create) {
    unsigned int index = delayedHash(key) % (unsigned int)heaps->delayedCapacity;
    while (heaps->delayed[index].used) {
        if (heaps->delayed[index].key == key) {
            return &heaps->delayed[index];
        }
        index = (index + 1) % (unsigned int)heaps->delayedCapacity;
    }
    if (!create) {
        return NULL;
    }
    heaps->delayed[index].key = key;
    heaps->delayed[index].count = 0;
    heaps->delayed[index].used = true;
    return &heaps->delayed[index];
}

static bool higherPriority(MedianHeap* heap, int a, int b) {
    return heap->isMax ? a > b : a < b;
}

static void heapPush(MedianHeap* heap, int num) {
    int i = heap->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!higherPriority(heap, num, heap->data[parent])) {
            break;
        }
        heap->data[i] = heap->data[parent];
        i = parent;
    }
    heap->data[i] = num;
}

static int heapPop(MedianHeap* heap) {
    int top = heap->data[0];
    int num = heap->data[--heap->size];
    if (heap->size == 0) {
        return top;
    }
    int i = 0;
    while (2 * i + 1 < heap->size) {
        int child = 2 * i + 1;
        if (child + 1 < heap->size &&
            higherPriority(heap, heap->data[child + 1], heap->data[child])) {
            ++child;
        }
        if (!higherPriority(heap, heap->data[child], num)) {
            break;
        }
        heap->data[i] = heap->data[child];
        i = child;
    }
    heap->data[i] = num;
    return top;
}

static void prune(DualHeap* heaps, MedianHeap* heap) {
    while (heap->size > 0) {
        int num = heap->data[0];
        DelayedEntry* entry = findDelayed(heaps, num, false);
        if (entry == NULL || entry->count == 0) {
            break;
        }
        --entry->count;
        heapPop(heap);
    }
}

static void balance(DualHeap* heaps) {
    if (heaps->leftSize > heaps->rightSize + 1) {
        int num = heapPop(&heaps->left);
        heapPush(&heaps->right, num);
        heaps->sumR += num;
        heaps->sumL -= num;
        ++heaps->rightSize;
        --heaps->leftSize;
        prune(heaps, &heaps->left);
    } else if (heaps->rightSize > heaps->leftSize) {
        int num = heapPop(&heaps->right);
        heapPush(&heaps->left, num);
        heaps->sumL += num;
        heaps->sumR -= num;
        ++heaps->leftSize;
        --heaps->rightSize;
        prune(heaps, &heaps->right);
    }
}

static void addNum(DualHeap* heaps, int num) {
    if (heaps->left.size == 0 || num <= heaps->left.data[0]) {
        heapPush(&heaps->left, num);
        ++heaps->leftSize;
        heaps->sumL += num;
    } else {
        heapPush(&heaps->right, num);
        ++heaps->rightSize;
        heaps->sumR += num;
    }
    balance(heaps);
}

static void removeNum(DualHeap* heaps, int num) {
    DelayedEntry* entry = findDelayed(heaps, num, true);
    ++entry->count;
    if (num <= heaps->left.data[0]) {
        --heaps->leftSize;
        heaps->sumL -= num;
        if (num == heaps->left.data[0]) {
            prune(heaps, &heaps->left);
        }
    } else {
        --heaps->rightSize;
        heaps->sumR -= num;
        if (num == heaps->right.data[0]) {
            prune(heaps, &heaps->right);
        }
    }
    balance(heaps);
}

long long minOperations(int* nums, int numsSize, int x, int k) {
    int n = numsSize;
    DualHeap heaps = {0};
    heaps.left.data = malloc(sizeof(int) * n);
    heaps.left.isMax = true;
    heaps.right.data = malloc(sizeof(int) * n);
    heaps.delayedCapacity = 2 * n + 1;
    heaps.delayed = calloc(heaps.delayedCapacity, sizeof(DelayedEntry));
    long long* ops = calloc(n, sizeof(long long));

    for (int i = 0; i < n; ++i) {
        addNum(&heaps, nums[i]);
        if (i >= x) {
            removeNum(&heaps, nums[i - x]);
        }
        if (i >= x - 1) {
            long long mid = heaps.left.data[0];
            ops[i] = heaps.sumR - heaps.sumL +
                     mid * (heaps.leftSize - heaps.rightSize);
        }
    }

    long long (*dp)[k + 1] = calloc(n, sizeof(long long) * (k + 1));
    for (int i = 0; i < n; ++i) {
        dp[i][0] = 0;
        for (int j = 1; j <= k; ++j) {
            dp[i][j] = LLONG_MAX;
        }
    }
    for (int j = 1; j <= k; ++j) {
        if (j == 1) {
            dp[x - 1][j] = ops[x - 1];
        } else {
            dp[j * x - 1][j] = dp[(j - 1) * x - 1][j - 1] + ops[j * x - 1];
        }
    }
    for (int j = 1; j <= k; ++j) {
        for (int i = j * x; i < n; ++i) {
            long long cost = dp[i - x][j - 1] + ops[i];
            dp[i][j] = cost < dp[i - 1][j] ? cost : dp[i - 1][j];
        }
    }

    long long answer = dp[n - 1][k];
    free(heaps.delayed);
    free(heaps.left.data);
    free(heaps.right.data);
    free(ops);
    free(dp);
    return answer;
}
