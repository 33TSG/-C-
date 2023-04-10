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
	Perm������������
	ist - ->ԭʼ���У����ÿһ��ľ��ı��
	level->�������ڼ���
	k-- > list ����������ʼλ��
	m-- > list �����������λ��
	Count->�ڼ���ľ�ϣ�ľ�ϵ�����
	set->��ά���󣬴��ÿһ��ľ���зŵ��ǵڼ���ľ�飬set[i][i] = 1��ʾ��i��ľ�Ͽ�
	�Ծ�ɵڡ���ľ��
	nlist->��ǰ���д�ŵ�list �еĵڼ���ľ�飬��������п�����ɵ�ǰľ�ϵ�ľ��
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