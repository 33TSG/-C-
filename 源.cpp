#include <iostream>
#include <string>
using namespace std;

string removeKdigits(string num, int k) {
    // num = "1432219" k = 3
    string res;
    int n = num.size(), keep = n - k;
    for (char c : num) {
        while (k > 0 && !res.empty() && res.back() > c) {
            res.pop_back();
            k--;
        }
        res.push_back(c);
    }
    res.resize(keep);
    while (!res.empty() && res.front() == '0') res.erase(res.begin());
    return res.empty() ? "0" : res;
}

int main() {
    string num;
    int k;
    cout << "Please enter a non-negative integer: ";
    cin >> num;
    cout << "Please enter the number of digits to be removed: ";
    cin >> k;
    cout << "The smallest number with " << k << " digits removed is: " << removeKdigits(num, k) << endl;
    return 0;
}

