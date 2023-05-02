#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main() {
	int w[5] = { 0 , 2 , 3 , 4 , 5 };			//��Ʒ�����2��3��4��5
	int v[5] = { 0 , 3 , 4 , 5 , 6 };			//��Ʒ�ļ�ֵ3��4��5��6
	int bagV = 8;					        //������С
	int dp[5][9] = { { 0 } };
	
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 8; j++) {
			if (w[i] > j) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			}
		}
	}

	cout << dp[4][8] << endl;

	return 0;
}
