#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100000

using namespace std;

struct Brick {
    int price;
    int copper;
};

// �ݹ麯�������ڼ��������
void combination(vector<int>& nums, int k, vector<int>& path, vector<vector<int>>& res, int start) {
    // �жϵݹ���ֹ��������� path ���Ѿ����� k ��Ԫ�أ�˵���ҵ���һ�����
    if (path.size() == k) {
        res.push_back(path); // ���ҵ�����ϴ洢�� res ��
        return;
    }
    // �� start ��ʼ���� nums
    for (int i = start; i < nums.size(); i++) {
        path.push_back(nums[i]); // ����ǰԪ�ؼ��� path ��
        combination(nums, k, path, res, i + 1); // ������һ��ݹ飬start ��Ϊ i+1�������ظ�ѡȡͬһԪ��
        path.pop_back(); // ���ݵ���һ��ݹ飬�������ӵ�Ԫ�ص���
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
    int n; // ����������ש����
    cin >> n;

    vector<Brick> bricks(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> bricks[i].copper >> bricks[i].price;
    }

    int c; // �˿�����
    cin >> c;

    while (c--) {
        int m, cmin, cmax;
        cin >> m >> cmin >> cmax;

        int ans = MAX;

        vector<int> path;
        vector<vector<int>> res;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = i + 1; // ��ʼ�� nums ����Ϊ 1,2,3,...,n
        }
        combination(nums, m, path, res, 0);         // ���õݹ麯���������

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