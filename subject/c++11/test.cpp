#include <vector>
#include <iostream>
using namespace std;

int main()
{
    vector<int> vec(5,0);
    vec.push_back(3);

    cout << "use for size" <<endl;
    int size = vec.size();
    for (int i = 0; i < size; ++ i) {
        cout<<vec[i]<<endl;
    }

    cout << "use for iterator" <<endl;
    for (auto it = vec.begin(); it != vec.end(); ++ it) {
        cout<<*it<<endl;
    }

    cout << "use for each" <<endl;
    for (auto &i : vec) {
        cout<<i<<endl;
    }
    return 0;
}
