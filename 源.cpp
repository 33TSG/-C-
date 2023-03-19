#include <iostream>
#include <vector>
using namespace std;

class Graph {        // ����ͼ
public:
    int v, e;                   // v �Ƕ������� e�Ǳߵ���Ŀ
    bool* visited;             //�Ƕ������ʹ�
    vector<vector<bool>> matrix;        //�ڽӾ���
    Graph() {
        cout << "���붥�����ͱ���" << endl;
        cin >> v >> e;
        matrix = vector<vector<bool>>(v, vector<bool>(v, false));
        visited = new bool[v] {false};
        for (int i = 0; i < e; ++i) {
            cout << "���������ڱߵ��������㣨a -> b��";
            int a, b;            // ��������
            cout << endl;
            cin >> a >> b;
            matrix[a][b] = true;    // a -> b��һ����
        }
    }

    void ts_visit(int node, vector<int>& res) {
        if (!visited[node]) {
            bool flag{ false };  // �Ƿ��нڵ㵽node
            for (int i = 0; i < v; ++i) {
                if (matrix[i][node]) {
                    flag = true;
                    break;
                }
            }
            if (!flag)      // ���û�нڵ㵽node���node�����ʹ���
            {
                visited[node] = true;
                res.push_back(node);
                for (int i = 0; i < v; ++i) {
                    if (matrix[node][i]) {
                        matrix[node][i] = false;    // ���ýڵ���ص�����ȫ��ȥ��
                        ts_visit(i, res);
                    }
                }
            }
        }
    }

    vector<int> TopologicalSort() {     // ���������㷨
        vector<int> res;
        while (res.size() != v) {
            for (int i = 0; i < matrix.size(); ++i) {
                ts_visit(i, res);
            }
        }
        return res;
    }

    void print() {                   // ��ӡ�ٽӾ���
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < v; ++j) {
                cout << matrix[i][j] << "  ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    vector<int> res = g.TopologicalSort();
    cout << "������������" << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << (i == res.size() - 1 ? "" : "->");
    }
    return 0;
}

/*��������
���룺
6 8                         7 7
0 1            v1 v2        1 0     b a
0 2            v1 v3        1 3     b d
0 3            v1 v4        0 6     a g
2 1            v3 v2        3 4     d e
2 4            v3 v5        3 5     d f
3 4            v4 v5        2 5     c f
5 3            v6 v4        2 6     c g
5 4            v6 v5

*/