# include "header.h"

// 16
int threeSumClosest(vector<int>& nums, int target) {
    int res = 0, min = 20000;
    for (int i = 0; i < nums.size() - 2; ++ i) {
        for (int j = i + 1; j < nums.size() - 1; ++ j) {
            for (int k = j + 1; k < nums.size(); ++ k) {
                int sum = nums[i] + nums[j] + nums[k];
                int gap = sum > target ? sum - target : target - sum;
                if (gap < min) {
                    min = gap;
                    res = sum;
                }
            }
        }
    }
    return res;
}

// 18
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int size = nums.size();
    vector<vector<int>> res;
    for (int i = 0; i < size - 3; ++ i) {
        if (i > 0 && nums[i] == nums[i-1]) {continue;}
        if (nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) {break;}
        if (nums[i] + nums[size-3] + nums[size-2] + nums[size-1] < target) {continue;}
        for(int j = i + 1; j < size -2; ++ j) {
            if (j > i + 1 && nums[j] == nums[j-1]) {continue;}
            if (nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) {break;}
            if (nums[i] + nums[j] + nums[size-2] + nums[size-1] < target) {continue;}
            int left = j + 1, right = size - 1;
            while (left < right) {
                int sum = nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    vector<int> tmp = {nums[i], nums[j], nums[left], nums[right]};
    cout << nums[i] << " " << nums[j] << " " << nums[left] << " " << nums[right] << endl;
                    res.push_back(tmp);
                    while (left < right && nums[left] == nums[left+1]) {
                        left++;
                    }
                    left++;
                    while (right > left && nums[right] == nums[right-1]) {
                        right--;
                    }
                    right--;
                } else if (sum < target) {
                    while (left < right && nums[left] == nums[left+1]) {
                        left++;
                    }
                    left++;
                } else {
                    while (right > left && nums[right] == nums[right-1]) {
                        right--;
                    }
                    right--;
                }
            }
        }
    }
    return res;
}

void test_two_pointer() {
    vector<int> vec = {-2,-1,-1,1,1,2,2};
    fourSum(vec, 0);
}
