#include <iostream>
#include <vector>
using namespace std;

typedef struct process {
    char ch;
    int etime;
} process;

char getMaxtime(vector<process>& arr) {
    int maxx = -1;
    for (int i = 0; i < arr.size(); i++) {
        maxx = max(maxx, arr[i].etime);
    }
    for (int i = 0; i < arr.size(); i++) {
        if (maxx == arr[i].etime) {
            return arr[i].ch;
        }
    }
}

int main() {
    int n;
    int k;
    vector<process> arr;
    cout << "输入需要执行进程的个数以及相同进程的间隔：" << endl;
    cin >> n >> k;
    char ch;
    cout << "输入进程名称：" << endl;
    int i, j;
    for (i = 0; i < n; i++) {
        cin >> ch;
        if (!arr.size()) {
            process p1;
            p1.ch = ch;
            p1.etime = 1;
            arr.push_back(p1);
        }
        else {
            for (j = 0; j < arr.size(); j++) {
                if (ch == arr[j].ch) {
                    arr[j].etime++;
                    break;
                }
            }
            if (j == arr.size()) {
                process p1;
                p1.ch = ch;
                p1.etime = 1;
                arr.push_back(p1);
            }
        }
    }
    int count = 0;
    vector<char> ans;
    vector<process> wt;
    while (count < n) {
        int j;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].etime) {
                for (j = 1; j <= k; j++) {
                    if (int(ans.size() - j) < 0) {
                        j = k + 1;
                        break;
                    }
                    if (arr[i].ch == ans[int(ans.size() - j)]) {
                        break;
                    }
                }
                if (j == k + 1) {
                    wt.push_back(arr[i]);
                }
            }
        }
        if (int(wt.size()) == 0) {
            ans.push_back('w');
        }
        else {
            int q;
            for (q = 0; q < arr.size(); q++) {
                char ch1 = getMaxtime(wt);
                if (arr[q].ch == ch1) {
                    ans.push_back(arr[q].ch);
                    arr[q].etime--;
                    count++;
                }
            }
        }
        wt.clear();
    }
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << endl <<  ans.size() << endl;
}
