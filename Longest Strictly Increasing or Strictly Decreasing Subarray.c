int longestMonotonicSubarray(int* nums, int numsSize) {
    int maxLength = 0;

    // Increasing subarray
    for (int start = 0; start < numsSize; start++) {
        int currLength = 1;

        for (int pos = start + 1; pos < numsSize; pos++) {
            if (nums[pos] > nums[pos - 1]) {
                currLength++;
            } else {
                break;
            }
        }

        if (currLength > maxLength)
            maxLength = currLength;
    }

    // Decreasing subarray
    for (int start = 0; start < numsSize; start++) {
        int currLength = 1;

        for (int pos = start + 1; pos < numsSize; pos++) {
            if (nums[pos] < nums[pos - 1]) {
                currLength++;
            } else {
                break;
            }
        }

        if (currLength > maxLength)
            maxLength = currLength;
    }

    return maxLength;
}
