# include "header.h"

// 5 7 7 8 8 10
void search(vector<int>& nums, int target, int l, int r, int& left, int& right, bool lf, bool rf) {
    while (l <= r) {
        int half = (r - l) / 2 + l;
        if (nums[half] > target) {
            r = half - 1;
        } else if (nums[half] < target) {
            l = half + 1;
        } else {
            if (lf) {
                if (half == l || (half > l && nums[half-1] != target)) {
                    left = half;
                } else {
                    search(nums, target, l, half - 1, left, right, true, false);
                }
            }
            if (rf) {
                if (half == r || (half < r && nums[half+1] != target)) {
                    right = half;
                } else {
                    search(nums, target, half + 1, r, left, right, false, true);
                }
            }
            break;
        }
    }
}
vector<int> searchRange(vector<int>& nums, int target) {
    int left = -1, right = -1;
    search(nums, target, 0, nums.size() - 1, left, right, true, true);
    return {left, right};
}

void test_binary_search() {
}
