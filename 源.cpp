#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param str string字符串
     * @param pattern string字符串
     * @return bool布尔型
     */
    bool match(string str, string pattern) {
        // write code here
        if (pattern.empty())
            return str.empty();
        vector<vector<bool>> dp(str.size() + 1, vector<bool>(pattern.size() + 1, false));
        // 初始化str = ""时pattern的匹配情况
        dp[0][0] = true;
        for (int j = 1; j <= pattern.size(); ++j) {
            if (pattern[j - 1] == '*')
                dp[0][j] = dp[0][j - 2];
        }

        for (int i = 1; i <= str.size(); ++i) {
            for (int j = 1; j <= pattern.size(); ++j) {
                if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (pattern[j - 1] == '*') {
                    if (dp[i][j - 1]) {       // 星号匹配一次，匹配一次是匹配多次的特殊情况，
                        dp[i][j] = dp[i][j - 1];
                    }
                    else if (j >= 2 && dp[i][j - 2]) {      // 星号匹配零次
                        dp[i][j] = dp[i][j - 2];
                    }
                    else if (i >= 2 && j >= 2) {      // 星号匹配多次
                        dp[i][j] = (dp[i - 1][j] && str[i - 1] == pattern[j - 2] || pattern[j - 2] == '.');
                    }
                }
            }
        }
        return dp[str.size()][pattern.size()];
    }
};

int main() {
    Solution* s = new Solution();
    cout << s->match("aad", "c*a*d");
    return 0;
}
