#include <iostream>
#include <vector>
using namespace std;

class Graph {        // 有向图
public:
    int v, e;                   // v 是顶点数， e是边的数目
    bool* visited;             //是都被访问过
    vector<vector<bool>> matrix;        //邻接矩阵
    Graph() {
        cout << "输入顶点数和边数" << endl;
        cin >> v >> e;
        matrix = vector<vector<bool>>(v, vector<bool>(v, false));
        visited = new bool[v] {false};
        for (int i = 0; i < e; ++i) {
            cout << "请输入相邻边的两个顶点（a -> b）";
            int a, b;            // 两个顶点
            cout << endl;
            cin >> a >> b;
            matrix[a][b] = true;    // a -> b有一条边
        }
    }

    void ts_visit(int node, vector<int>& res) {
        if (!visited[node]) {
            bool flag{ false };  // 是否有节点到node
            for (int i = 0; i < v; ++i) {
                if (matrix[i][node]) {
                    flag = true;
                    break;
                }
            }
            if (!flag)      // 如果没有节点到node标记node被访问过了
            {
                visited[node] = true;
                res.push_back(node);
                for (int i = 0; i < v; ++i) {
                    if (matrix[node][i]) {
                        matrix[node][i] = false;    // 将该节点相关的连线全部去除
                        ts_visit(i, res);
                    }
                }
            }
        }
    }

    vector<int> TopologicalSort() {     // 拓扑排序算法
        vector<int> res;
        while (res.size() != v) {
            for (int i = 0; i < matrix.size(); ++i) {
                ts_visit(i, res);
            }
        }
        return res;
    }

    void print() {                   // 打印临接矩阵
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
    cout << "拓扑排序结果：" << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << (i == res.size() - 1 ? "" : "->");
    }
    return 0;
}

/*测试数据
输入：
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