#include<iostream>
#include<conio.h>
#define MAXM 10
using namespace std;
void Perm(int*, int, int, int, int, int set[MAXM][MAXM], int nlist[MAXM]);
int qlist[MAXM];
int loss;
int n, len, mn = 0;

int main() {
	int* list;
	int set[MAXM][MAXM];
	int nlist[MAXM];
	memset(qlist, 0, sizeof(qlist));
	cin >> len;
	cin >> loss;
	n = 0;
	while (cin >> qlist[n] && qlist[n] != -1)
		n++;
	mn = n;
	list = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		list[i] = i;
	}
	memset(set, 0, sizeof(set));
	memset(nlist, 0, sizeof(nlist));
	Perm(list, 0, 0, n - 1, 1, set, nlist);
	cout << mn << endl;
	return 0;
}
/*
	Perm函数参数定义
	ist - ->原始序列，存放每一个木块的编号
	level->搜索到第几层
	k-- > list 中搜索的起始位置
	m-- > list 中搜索的最后位置
	Count->第几块木料，木料的数量
	set->二维矩阵，存放每一块木料中放的是第几个木块，set[i][i] = 1表示第i块木料可
	以锯成第」块木块
	nlist->当前树中存放的list 中的第几个木块，存放了所有可以组成当前木料的木块
*/
void Perm(int* list, int level, int k, int m, int count, int set[MAXM][MAXM], int nlist[MAXM]) {
	int i;
	int nset[MAXM][MAXM];
	int mlist[MAXM];
	int klist[MAXM];
	if (m == 0) {
		for (int l = k; l <= m; l++) {
			set[count - 1][list[l]] = 1;
		}
		int flag = 0;
		for (int l = 0; l <= count; l++) {
			int sum = 0;
			for (int h = 0; h < n; h++) {
				if (set[l][h] == 1) {
					sum += qlist[h] + loss;
				}
			}
			if (sum > len + loss) {
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			mn = mn > count ? count : mn;
		return;
	}
	if (k > m) {
		return;
	}
	else {
		for (i = k; i <= m; i++) {
			for (int l = 0; l < level; l++)
				klist[l] = nlist[l];
			klist[level] = list[i];
			int left = 0;
			for (int l = 0; l <= m; l++) {
				int s;
				for (s = 0; s <= level; s++) {
					if (list[l] == klist[s])
						break;
				}
				if (s > level)
					mlist[left++] = list[l];
			}
			for (int l = 0; l < MAXM; l++) {
				for (int h = 0; h < MAXM; h++) {
					nset[l][h] = set[l][h];
				}
			}
			for (int l = 0; l <= level; l++) {
				nset[count - 1][klist[l]] = 1;
			}
			left--;
			if (left < 0) {
				int flag = 0;
				for (int l = 0; l < count; l++) {
					int sum = 0;
					for (int h = 0; h < n; h++) {
						if (nset[l][h] == 1) {
							sum += qlist[h] + loss;
						}
					}
					if (sum > len + loss) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					mn = mn > count ? count : mn;
				}
			}
			Perm(mlist, 0, 0, left, count+1, nset, klist);
			Perm(list, level+1, i+1, m, count, set, klist);
		}
	}
}