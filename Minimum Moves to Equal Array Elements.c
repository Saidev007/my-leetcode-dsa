int minMoves(int* nums, int numsSize) {
    int min = nums[0];
    int sum = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }

        sum += nums[i];
    }

    return sum - (numsSize * min);
}
