#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100000

using namespace std;

struct Brick {
    int price;
    int copper;
};

int main() {
    int n; // 工厂生产的砖种数
    cin >> n;

    vector<Brick> bricks(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> bricks[i].price >> bricks[i].copper;
    }

    int c; // 顾客数量
    cin >> c;

    while (c--) {
        int m, cmin, cmax;
        cin >> m >> cmin >> cmax;

        vector<int> costs; // 存储满足要求的所有砖的价格
        // f[i][j] 表示当要买i块砖头，含铜量为j时的最小价格
        vector<vector<int>> dp(m + 1, vector<int>(cmax + 1, MAX));

        sort(bricks.begin(), bricks.end(), [](Brick a, Brick b) {    // 按含铜量升序排序
            return a.copper < b.copper;
        });
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int k = 1; k <= cmax; ++k) {
                    if (k >= bricks[i].copper) {
                        dp[j][k] = min(dp[j][k], dp[j - 1][k - bricks[i].copper] + bricks[i].price);
                    }
                }
            }
        }

        int ans = MAX;
        for (int i = cmin; i <= cmax; ++i) {
            ans = min(ans, dp[m][i]);
        }

        if (ans != MAX)
            cout << ans << endl;
        else
            cout << "NO" << endl;

    }

    return 0;
}

