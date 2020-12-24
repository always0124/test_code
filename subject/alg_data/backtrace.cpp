# include "header.h"

void backTrace(vector<int>& candidates, int start, int target, vector<int>& list, vector<vector<int>>& res) {
    if (target == 0) {
        res.emplace_back(list);
        return;
    }
    if (target < 0 || start >= candidates.size()) {
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        int item = candidates[i];
        int cur = item;
        if (cur > target) {
            break;
        }
        list.push_back(item);
        backTrace(candidates, i, target - cur, list, res);
        list.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> list;
    sort(candidates.begin(), candidates.end());
    backTrace(candidates, 0, target, list,res);
    return res;
}

void dfs(vector<int>& nums, int start, bool& flag, int& res) {
    int max = start + nums[start];
    if (max >= nums.size() - 1) {
        res++;
        flag = true;
        return;
    }
    for (int i = max; i > start; -- i) {
        res++;
        dfs(nums, i, flag, res);
        if (flag) return;
        res--;
    }
}
int jump(vector<int>& nums) {
    int size = nums.size();
    if (size <= 1) return 0;
    int res = 0;
    bool flag = false;
    dfs(nums, 0, flag, res);
    return res;
}

void queen_dfs(int& res, int n, int index, vector<int>& h1, vector<int>& h2, map<int,int>& m1) {
    if (n == index) {
        res++;
        return;
    }
    for (int i = 0; i < n; ++i) {
        int gap = index - i;
        int sum = index + i;
        if (h1[i] == 1 || h2[sum] == 1 || m1[gap] == 1) {
            continue;
        }
        h1[i] = h2[sum]  = m1[gap] = 1;
        queen_dfs(res, n, index+1,h1, h2, m1);
        h1[i] = h2[sum] = m1[gap] = 0;
    }
}

int totalNQueens(int n) {
    int res = 0;
    vector<int> h1(n,0), h2(2*n, 0);
    map<int, int> m1;
    queen_dfs(res, n, 0, h1, h2, m1);
    return res;
}

void test_backtrace() {
    totalNQueens(4);
}
