#include <vector>
#include <map>
#include <stdio.h>

using namespace std;

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

void test_string()
{
    string cas_res = countAndSay(4);
    cout<< cas_res << endl;
    return;
}
