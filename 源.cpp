#include <iostream>
#include <vector>

using namespace std;

bool ok(int n, vector<int>& pos) {                       // 判断两个皇后是都否在同一列，同一斜线上
    for (int i = 0; i < n; ++i) {       // 检查和前面放置的换后是否能攻击
        if (pos[n] == pos[i] || abs(i - n) == abs(pos[i] - pos[n]))
            return false;
    }
    return true;
}

void traceBack(vector<int>& pos, int& res, int n) {
    if (n == pos.size()) {
        res++;
    }
    else {
        for (int i = 0; i < pos.size(); ++i) {
            pos[n] = i;                     // 第n个皇后放在 (n, i)上
            if (ok(n, pos)) {            // 当第n个皇后放置在这个位置上可行时
                traceBack(pos, res, n + 1);
            }
            pos[n] = 0;     // 回溯
        }
    }
}

int NQueue(int n) {
    vector<int> pos(n, 0);         // 记录每一行皇后放置的位置
    int res{ 0 };
    traceBack(pos, res, 0);
    return res;
}

int main() {
    cout << NQueue(8);
    return 0;
}
