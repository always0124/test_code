# include "header.h"

bool isValidSudoku(vector<vector<char>>& board) {
    vector<char> vec(9, '0');
    int m = 9, n = 9;
    // 按行检查
    for (int i = 0; i < m; ++ i) {
        vector<char> tmp = vec;
        for (int j = 0; j < n; ++ j) {
            char ch = board[i][j];
            if (ch == '.') {
                continue;
            }
            if (tmp[ch-'1'] == '0') {
                tmp[ch-'1'] = ch;
            } else {
                return false;
            }
        }
    }
    // 按列检查
    for (int i = 0; i < n; ++ i) {
        vector<char> tmp = vec;
        for (int j = 0; j < m; ++ j) {
            char ch = board[j][i];
            if (ch == '.') {
                continue;
            }
            if (tmp[ch-'1'] == '0') {
                tmp[ch-'1'] = ch;
            } else {
                return false;
            }
        }
    }
    // 按九宫格检查
    vector<vector<int>> point = {{0,0}, {0,3}, {0,6},
                                 {3,0}, {3,3}, {3,6},
                                 {6,0}, {6,3}, {6,6}};
    for (int k = 0; k < 9; ++k) {
        m = point[k][0], n = point[k][1];
        vector<char> tmp = vec;
        for (int i = m; i < m + 3; ++ i) {
            for (int j = n; j < n + 3; ++ j) {
                char ch = board[i][j];
                if (ch == '.') {
                    continue;
                }
                if (tmp[ch-'1'] == '0') {
                    tmp[ch-'1'] = ch;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

bool isValidSudoku_new(vector<vector<char>>& board) {
    //vector<vector<char>> row(9, vector<char>(9, '0'));
    //vector<vector<char>> column(9, vector<char>(9, '0'));
    //vector<vector<char>> box(9, vector<char>(9, '0'));
    int row[9][9] = {0};
    int column[9][9] = {0};
    int box[9][9] = {0};
    for (int i = 0; i < 9; ++ i) {
        for (int j = 0; j < 9; ++ j) {
            char ch = board[i][j];
            if (ch != '.') {
                int index = ch - '1';
                if (row[i][index] || column[j][index] || box[i/3*3 + j/3][index]) return false;
                row[i][index] = column[j][index] = box[i/3*3 + j/3][index] = 1;
            }
        }
    }
    return true;
}
void test_hash() {
}
