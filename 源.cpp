#include <iostream>
#include <vector>

using namespace std;

bool ok(int n, vector<int>& pos) {                       // �ж������ʺ��Ƕ�����ͬһ�У�ͬһб����
    for (int i = 0; i < n; ++i) {       // ����ǰ����õĻ����Ƿ��ܹ���
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
            pos[n] = i;                     // ��n���ʺ���� (n, i)��
            if (ok(n, pos)) {            // ����n���ʺ���������λ���Ͽ���ʱ
                traceBack(pos, res, n + 1);
            }
            pos[n] = 0;     // ����
        }
    }
}

int NQueue(int n) {
    vector<int> pos(n, 0);         // ��¼ÿһ�лʺ���õ�λ��
    int res{ 0 };
    traceBack(pos, res, 0);
    return res;
}

int main() {
    cout << NQueue(8);
    return 0;
}
