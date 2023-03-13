#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Graph {        // ����ͼ
public:
	int v, e;       // v �Ƕ������� e�Ǳߵ���Ŀ
	vector<vector<int>> matrix;        //�ڽӾ���

	Graph(int v, int e) : v(v), e(e) {
		matrix = vector<vector<int>>(v, vector<int>(v, 0));
		for (int i = 0; i < v; ++i) {
			cout << "���������ڵ��������㼰���ӱ��ϵ�Ȩֵ";
			int a, b, power;            // ���������Ȩֵ
			cout << endl;
			cin >> a >> b >> power;
			matrix[a][b] = matrix[b][a] = power;
		}
	}

	vector<vector<int>> prim() {
		vector<vector<int>> res(v, vector<int>(v, 0));
		vector<int> temp;               // �������еĶ���
		bool* exists = new bool[v];     //�����Ƿ��Ѿ��ڼ�����
		exists[0] = true;               //�ӵ�һ�����㿪ʼ����
		temp.push_back(0);

		while (temp.size() != v) {
			int dist = 1000, mark1 = 0, mark2 = 0;
			for (int i : temp) {
				for (int j = 0; j < v; ++j) {
					if (!exists[j] && matrix[i][j] != 0 && dist > matrix[i][j]) {
						dist = matrix[i][j];
						mark1 = i;
						mark2 = j;
					}
				}
			}
			exists[mark2] = true;
			temp.push_back(mark2);
			res[mark1][mark2] = res[mark2][mark1] = matrix[mark1][mark2];
		}
		return res;
	}

	void print(vector<vector<int>> Matrix) {
		for (int i = 0; i < v; ++i) {
			for (int j = 0; j < v; ++j) {
				cout << Matrix[i][j] << "  ";
			}
			cout << endl;
		}
	}
};

/*
 * 7  10
 * 0 1 5
 * 0 2 7
 * 0 6 2
 * 1 3 9
 * 1 6 3
 * 4 2 8
 * 4 6 4
 * 4 5 5
 * 5 6 6
 * 5 3 4
 */

int main() {
	int m, n;
	cout << "����ͼ�Ķ������ͱ�����" << endl;
	cin >> m >> n;
	Graph g(m, n);
	cout << "prim�㷨��С���������ڽӾ���" << endl;
	g.print(g.prim());
	return 0;
}
