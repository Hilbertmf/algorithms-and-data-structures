#include <bits/stdc++.h> 
using namespace std;

int advance_right(string& s, int left, int right) {
    while(right < s.size() && s[right - left] == s[right]) {
        ++right;
    }
    --right;
    return right;
}

vector<int> z_func(string& pattern, string& text) {

    string s = pattern + "$" + text;
    vector<int> z(s.size());
    int left = 0, right = 0;

    for(int i = 1; i < s.size(); ++i) {
        if(i > right) {
            left = right = i;
            right = advance_right(s, left, right);
            z[i] = right - left + 1;
        }
        else { // inside z-box
            int i1 = i - left;
            if(z[i1] < right - i + 1) { // if right can't exceed z-box
                z[i] = z[i1];
            }
            else {
                // reset z-box and try to expand it
                left = i;
                right = advance_right(s, left, right);
                z[i] = right - left + 1;
            }
        }
    }
    return z;
}

int main() {
    string txt, pat;
    cin >> pat >> txt;

    vector<int> z = z_func(pat, txt);
    vector<int> ans; // array w/ indices of pattern match

    for(int i = pat.size() + 1; i < z.size(); ++i) {
        if(z[i] == pat.size()) ans.push_back(i - pat.size() + 1);
    }

    for(auto &item : ans) {
        cout << item << " ";
    }

    return 0;
}