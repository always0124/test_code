# include "header.h"

class WordDict{
private:
    bool isEnd;
    WordDict* next[26];
private:
    bool dfs(string& word, WordDict* root, int index) {
        if (word.size() == index) return root->isEnd;
        if (word[index] == '.') {
            for (auto& item : root->next) {
                if (item && dfs(word, item, index+1)) return true;
            }
            return false;
        } else {
            int i = word[index] - 'a';
            if (root->next[i] == nullptr) return false;
            return dfs(word, root->next[i], index+1);
        }
    }
    void dfsN(string& word, WordDict* root, int index, int& res) {
        if (word.size() == index) {
            if (root->isEnd) res++;
            return;
        }
        if (word[index] == '.') {
            for (auto& item : root->next) {
                if (item) {
                    dfsN(word, item, index+1, res);
                }
            }
        } else {
            int i = word[index] - 'a';
            if (root->next[i] == nullptr) return;
            dfsN(word, root->next[i], index+1, res);
        }
    }
public:
    WordDict() {
        memset(next, 0, sizeof(next));
        isEnd = false;
    }
    // insert one word
    void insertWord(string& word) {
        WordDict* root = this;
        for (auto& c : word) {
            int index = c - 'a';
            if (root->next[index] == nullptr) {
                root->next[index] = new WordDict();
            }
            root = root->next[index];
        }
        root->isEnd = true;
    }
    // find if word exist, return true or false, word maybe contain '.' match any character
    bool searchWord(string& word) {
        WordDict* root = this;
        return dfs(word, root, 0);
    }
    // return how many words contain the given word
    int getNums(string& word) {
        WordDict* root = this;
        int res = 0;
        dfsN(word, root, 0, res);
        return res;
    }
};

void test_trie() {
    WordDict dict;
    string ad("ad");
    string ade("ade");
    string aes("aes");
    string a("ade");
    string b("b");
    string e("e");
    dict.insertWord(ad);
    dict.insertWord(ade);
    dict.insertWord(aes);
    cout << "a:" << dict.getNums(a) << ", b:" << dict.getNums(b) << ", e:" << dict.getNums(e) <<endl;
}
