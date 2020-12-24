# include "header.h"

// 38
string countAndSay(int n) {
    if (n == 1) return "1";
    string res;
    string last = countAndSay(n-1);
    int num = 1;
    for (int i = 0; i < last.size(); ++ i) {
        if (last[i] != last[i+1]) {
            res += to_string(num) + last[i];
            num = 1;
        } else {
            num++;
        }
    }
    return res;
}

// 43
string multiply(string num1, string num2) {
    int len1 = num1.size(), len2 = num2.size();
    if (len1 == 0 || len2 == 0) {
        return "";
    }
    if (num1[0] == '0' || num2[0] == '0') {
        return "0";
    }

    vector<int> vec(len1+len2, 0);
    int carry = 0, cur = 0;
    for (int i = len2 - 1; i >= 0; -- i) {
        for (int j = len1 - 1; j >= 0; -- j) {
            int vec_index = len2-i+len1-j-2;
            cur = vec[vec_index] + (num1[j] - '0')*(num2[i] - '0') + carry;
            vec[vec_index] = cur % 10;
            carry = cur / 10;
        }
        if (carry > 0) {
            vec[len1+len2-i-1] = carry;
            carry = 0;
        }
    }
    if (carry > 0) {
        vec[len1+len2-1] = carry;
    }
    int start = len1 + len2 -1;
    if (vec[start] == 0) {
        start --;
    }
    string res("");
    for (int i = start; i >= 0; -- i) {
        res += to_string(vec[i]);
    }
    return res;
}

// 49
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> hash;
    for (int i = 0; i < strs.size(); ++ i) {
        string str = strs[i];
        sort(str.begin(), str.end());
        hash[str].push_back(strs[i]);
    }

    vector<vector<string>> res;
    for (auto& item : hash) {
        res.push_back(item.second);
    }
    return res;
}

// 65
bool isNumber(string s) {
    if (s.empty()) {
        return false;
    }
    int size = s.size();
    int index = 0;
    while (s[index] == ' ' && index < size) {
        index++;
    }
    if (index == size) {
        return false;
    }
    bool e_flag = false; //只能出现1次且前后都必须有数字且后不能有小数点
    bool p_flag = false; // 只能出现1次且只能出现在e的前面
    if (s[index] == '.') {
        p_flag = true;
        if (index  == size -1) {
            return false;
        }
    } else if (s[index] != '+' && s[index] != '-' && (s[index] < '0' || s[index] > '9')) {
        return false;
    }
    index++;
    while (index < size) {
        if ((s[index] == 'e' || s[index] == '.' || s[index] == ' ') && (s[index-1] == '-' || s[index-1] == '+')) {
            return false;
        }
        if ((s[index] == 'e' || s[index] == '.') && e_flag) {
            return false;
        }
        if (s[index] == '.' && p_flag) {
            return false;
        }
        if (s[index] == ' ') {
            if (s[index-1] == 'e' || (s[index-1] == '.' && (index - 2 < 0 || (s[index-2] < '0' || s[index-2] > '9')))) {
                return false;
            }
            break;
        }
        if (s[index] != 'e' && s[index] != '.' && (s[index] < '0' || s[index] > '9')) {
            return false;
        }
        if (s[index] == 'e') {
            e_flag = true;
            if (index == size-1 || s[index-1] == '.') {
                return false;
            }
        }
        if (s[index] == '.') {
            p_flag = true;
        }
        index++;
    }
    while (index < size) {
        if (s[index] != ' ') {
            return false;
        }
        index++;
    }
    return true;
}

// 67
string addBinary(string a, string b) {
    string res("");
    int carry = 0, index = 0;
    int l1 = a.size(), l2 = b.size();
    for (; index < l1 && index < l2; ++ index) {
        int sum = a[l1-index-1] - '0' + b[l2-index-1] - '0' + carry;
        if (sum%2 == 1) {
            res.push_back('1');
        } else {
            res.push_back('0');
        }
        carry = sum / 2;
    }
    while (index < l1) {
        int sum = a[l1-index-1] - '0' + carry;
        if (sum%2 == 1) {
            res.push_back('1');
        } else {
            res.push_back('0');
        }
        carry = sum / 2;
        index++;
    }
    while (index < l2) {
        int sum = b[l2-index-1] - '0' + carry;
        if (sum%2 == 1) {
            res.push_back('1');
        } else {
            res.push_back('0');
        }
        carry = sum / 2;
        index++;
    }
    if (carry == 1) {
        res.push_back('1');
    }
    reverse(res.begin(), res.end());
    return res;
}

// 68
void deal(vector<string>& words, int start, int end, int blank_num, string& line) {
    line.clear();
    if (start == end) {
        line = words[start];
        while (blank_num > 0) {
            line += " ";
            blank_num --;
        }
        return;
    }
    int remain = blank_num % (end - start);
    int num = blank_num / (end - start) + 1; // 加1是统计cur的时候就包含的
    int flag = start;
    if (remain == 0) {
        flag = end;
    } else {
        num++;
        flag += remain;
    }
    string b1(""), b2("");
    for (int i = 0; i < num - 1; ++ i) {
        b1 += " ";
        b2 += " ";
    }
    b1 += " ";
    for (int j = start; j < end; ++ j) {
        if (j < flag) {
            line += words[j] + b1;
        } else {
            line += words[j] + b2;
        }
    }
    line += words[end];
}
vector<string> fullJustify(vector<string>& words, int maxWidth) {
    int size = words.size();
    int start = 0; // 记录满足一行的数组元素的起始索引
    int cur = 0; // 当前长度，大于maxWidth则需要进行一行的整理
    string line("");
    vector<string> res;
    for (int i = 0; i < size; ++ i) {
        cur += words[i].size();
        if (cur > maxWidth) {
            deal(words, start, i - 1, maxWidth - cur + words[i].size() + 1,line);
            res.push_back(line);
            start = i;
            cur = words[i].size();
            cur ++;
        } else if (cur == maxWidth) {
            deal(words, start, i, 0, line);
            res.push_back(line);
            start = i + 1;
            cur = 0;
        } else {
            cur ++; // 空格
        }
    }
    // 最后一行
    line.clear();
    if (start == size) {
        return res;
    }
    while (start < size) {
        line += words[start];
        if (line.size() < maxWidth) {
            line += " ";
        }
        start++;
    }
    while (line.size() < maxWidth) {
        line += " ";
    }
    res.push_back(line);
    return res;
}

// 71
string simplifyPath(string path) {
    // .   ..   //
    vector<string> st;
    int start = 1;
    int size = path.size();
    for (int i = 1; i < size; ++ i) {
        if (path[i] == '/') {
            if (start < i) {
                string str = path.substr(start, i - start);
                if (str == "..") {
                    if (!st.empty()) {
                        st.pop_back();
                    }
                } else if (str != "."){
                    st.push_back(str);
                }
            }
            start = i + 1;
        }
    }
    if (start < size) {
        string str = path.substr(start);
        if (str == "..") {
            if (!st.empty()) {
                st.pop_back();
            }
        } else if (str != "."){
            st.push_back(str);
        }
    }
    string res("/");
    if (st.empty()) {
        return res;
    }
    int i = 0;
    for (; i < st.size() - 1; ++ i) {
        res += st[i] + "/";
    }
    res += st[i];
    return res;
}

void test_string()
{
    vector<string> vec = {"ask","not","what","your","country","can","do","for","you","ask","what","you","can","do","for","your","country"};
    vector<string> res = fullJustify(vec, 16);
    for (auto& i : res) {
        cout << i << endl;
    }
    return;
}
