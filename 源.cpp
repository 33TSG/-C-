#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100000

using namespace std;

struct Brick {
    int price;
    int copper;
};

// 递归函数，用于计算组合数
void combination(vector<int>& nums, int k, vector<int>& path, vector<vector<int>>& res, int start) {
    // 判断递归终止条件，如果 path 中已经有了 k 个元素，说明找到了一组组合
    if (path.size() == k) {
        res.push_back(path); // 将找到的组合存储到 res 中
        return;
    }
    // 从 start 开始遍历 nums
    for (int i = start; i < nums.size(); i++) {
        path.push_back(nums[i]); // 将当前元素加入 path 中
        combination(nums, k, path, res, i + 1); // 进行下一层递归，start 设为 i+1，避免重复选取同一元素
        path.pop_back(); // 回溯到上一层递归，将最后添加的元素弹出
    }
}

int sumCopper(vector<int>& nums, vector<Brick> &bricks) {
    int sum{ 0 };
    for (int i : nums)
        sum += bricks[i].copper;
    return sum;
}

int sumPrice(vector<int>& nums, vector<Brick>& bricks) {
    int sum{ 0 };
    for (int i : nums)
        sum += bricks[i].price;
    return sum;
}

int main() {
    int n; // 工厂生产的砖种数
    cin >> n;

    vector<Brick> bricks(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> bricks[i].copper >> bricks[i].price;
    }

    int c; // 顾客数量
    cin >> c;

    while (c--) {
        int m, cmin, cmax;
        cin >> m >> cmin >> cmax;

        int ans = MAX;

        vector<int> path;
        vector<vector<int>> res;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = i + 1; // 初始化 nums 数组为 1,2,3,...,n
        }
        combination(nums, m, path, res, 0);         // 调用递归函数求组合数

        for (auto &i: res) {
            if (sumCopper(i, bricks) >= cmin && sumCopper(i, bricks) <= cmax)
                ans = min(ans, sumPrice(i, bricks));
        }

        if (ans != MAX)
            cout << ans << endl;
        else
            cout << "NO" << endl;

    }

    return 0;
}