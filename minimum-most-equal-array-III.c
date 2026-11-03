int minMoves(int* nums, int numsSize) {
    int mx = nums[0];
    for (int i = 1; i < numsSize; i++) {
        mx = fmax(mx, nums[i]);
    }
    int ans = 0;
    for (int i = 0; i < numsSize; i++) {
        ans += mx - nums[i];
    }
    return ans;
}
