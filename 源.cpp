#include <iostream>
#include <algorithm>
#include <vector>

using namespace  std;

int FindGreatestSumOfSubArray(vector<int> array) {
    vector<int> dp(array.size(), 0);        // ��dp[i]λ�õ����ֵ
    int Max = dp[0] = array[0];
    for (int i = 1; i < array.size(); ++i) {
        dp[i] = max(array[i], array[i] + dp[i - 1]);
        Max = max(Max, dp[i]);
    }
    return Max;
}

int FindMaxSumOfSubMatrix(vector<vector<int>> matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<int> temp(m, 0);     // ���ڱ���������ӵ���ʱ����
    int sum = 0, Max = 0;

    for (int begin = 0; begin < n; begin++) {
        for (int k = 0; k < m; k++)
            temp[k] = 0;             //����Ϊ0����һ���ǳ��ؼ�

        for (int end = begin; end < n; end++) {
            for (int k = 0; k < m; k++)
                temp[k] += matrix[end][k];      //�ӿ�ʼ�е������н���ѹ����ѹ����һ��
            Max = FindGreatestSumOfSubArray(temp);//�����һ�����ݵ�����Ӷκ�
            sum = max(Max, sum);
        }
    }

    return sum;
}

int main()
{
    int n{ 0 };
    cin >> n;
    vector<vector<int>> matrix;
    vector<int> row;
    for (int i = 0; i < n; i++)
    {
        int t;
        for (int j = 0; j < n; j++)
        {
            cin >> t;
            row.push_back(t);
        }
        matrix.push_back(row);
        row.clear();
    }

    cout << FindMaxSumOfSubMatrix(matrix) << endl;
    return 0;
}