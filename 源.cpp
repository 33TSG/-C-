#include <iostream>
#include <algorithm>
#include <vector>

using namespace  std;

int FindGreatestSumOfSubArray(vector<int> array) {
    vector<int> dp(array.size(), 0);        // 到dp[i]位置的最大值
    int Max = dp[0] = array[0];
    for (int i = 1; i < array.size(); ++i) {
        dp[i] = max(array[i], array[i] + dp[i - 1]);
        Max = max(Max, dp[i]);
    }
    return Max;
}

int FindMaxSumOfSubMatrix(vector<vector<int>> matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<int> temp(m, 0);     // 用于保存数组相加的临时数组
    int sum = 0, Max = 0;

    for (int begin = 0; begin < n; begin++) {
        for (int k = 0; k < m; k++)
            temp[k] = 0;             //重置为0，这一步非常关键

        for (int end = begin; end < n; end++) {
            for (int k = 0; k < m; k++)
                temp[k] += matrix[end][k];      //从开始行到结束行进行压缩，压缩成一行
            Max = FindGreatestSumOfSubArray(temp);//求出这一行数据的最大子段和
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