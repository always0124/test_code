# include "header.h"

void quick_sort(vector<int>& vec, int low, int high){
    if (low >= high) return;
    int i = low;
    int j = high;
    while (i < j) {
        while (i<j && vec[j] >= vec[low])
            j--;
        vec[i] = vec[j];
        while (i<j && vec[i] <= vec[low])
            ++j;
        vec[j] = vec[i];
    }
    vec[i] = vec[low];
    quick_sort(vec, low, i-1);
    quick_sort(vec, i+1, high);
}

void adjust_heap(vector<int>& vec, int len, int root) {
    while (1) {
        // two leafs
        int left = 2 * root + 1, right = 2 * root + 2;
        if (left >= len) {
            break;
        }
        // choose max leaf
        int max = left;
        if (right < len && vec[right] > vec[max]) {
            max = right;
        }
        // compare max leaf with root, if max is bigger than root, then swap them and compare recursive
        if (vec[max] > vec[root]) {
            swap(vec[max], vec[root]);
            root = max;
        } else {
            break;
        }
    }
}

void heap_sort(vector<int>& vec){
    // make-heap
    int last_non_leaf = vec.size() / 2 - 1;
    for (int i = last_non_leaf; i >= 0; -- i) {
        adjust_heap(vec, vec.size(), i);
    }
    // heap sort
    for (int i = vec.size() - 1; i > 0; -- i) {
        swap(vec[0], vec[i]);
        adjust_heap(vec, i, 0);
    }
}

void merge(vector<int>& vec, int v1, int len1, int v2, int len2) {
    int max1 = v1 + len1, max2 = v2 + len2;
    vector<int> lvec(vec.begin()+v1, vec.begin()+max1);
    vector<int> rvec(vec.begin()+v2, vec.begin()+max2);
    int index = v1, i = 0, j = 0;
    while (i < len1 && j < len2) {
        int min = lvec[i] <= rvec[j] ? lvec[i++] : rvec[j++];
        vec[index++] = min;
    }
    while (i < len1) {
        vec[index++] = lvec[i++];
    }
    while (j < len2) {
        vec[index++] = rvec[j++];
    }
}

void merge_sort(vector<int>& vec, int left, int right){
    if (left >= right) {
        return;
    }
    int mid = (right - left) / 2 + left;
    merge_sort(vec, left, mid);
    merge_sort(vec, mid+1, right);
    merge(vec, left, mid - left + 1, mid + 1, right - mid);
}

void test_sort() {
    unordered_map<int, int> hash;
    hash[1] = 22;
    hash[12] = 2;
    hash[8] = 5;
    hash[6] = 15;
    auto iter = hash.begin();
    while (iter != hash.end()) {
        cout << iter->first << " " << iter->second <<endl;
        iter++;
    }
    return;
    vector<int> vec {10, 3, 2, 15, 29, 4, 8};
    //quick_sort(vec, 0, vec.size()-1);
    //heap_sort(vec);
    //merge_sort(vec, 0, vec.size() - 1);
    for (auto & i : vec) {
        cout << i << " ";
    }
    cout << endl;
}
