# include "header.h"

int findroot(int* root, int x){
    while(x != root[x]) {
        x = root[x];
    }
    return x;
}

int unionfind(int* root, int x, int y) {
    int r1 = findroot(root, x);
    int r2 = findroot(root, y);
    if (r1 == r2) return 0;
    root[r1] = r2;
    return 1;
}
int numislands(vector<vector<int>>& grid) {
    int x = grid.size();
    if (x == 0) return 0;
    int y = grid[0].size();
    int root[x*y];
    for (int i = 0; i < x; ++ i) {
        for (int j = 0; j < y; ++ j) {
            root[i*y+j] = i*y+j;
        }
    }
    int res = x*y;
    for (int i = 0; i < x; ++ i) {
        for (int j = 0; j < y; ++ j) {
            if (grid[i][j] == '1') {
                if (j+1 < y && grid[i][j+1] == '1') {
                    res -= unionfind(root, i*y+j, i*y+j+1);
                }
                if (i+1 < x && grid[i+1][j] == '1') {
                    res -= unionfind(root, i*y+j, (i+1)*y+j);
                }
            } else {
                res--;
            }
        }
    }
    return res;
}

void test_bingchaji() {
}
