#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

float getDistance(int a, int b, int c, int d) {
    return sqrt(pow(a - c, 2) + pow(b - d, 2));
}

void print(vector<pair<int, int>>& dots) {
    for (auto& dot : dots)
        cout << "(" << dot.first << "," << dot.second << ")";
    cout << endl;
}

float help(vector<pair<int, int>>& dots, int start, int end) {
    if (start == end - 1) {
        return getDistance(dots[start].first, dots[start].second,
            dots[end].first, dots[end].second);
    }
    float dl = help(dots, start, (start + end) / 2);
    float dr = help(dots, (start + end) / 2, end);
    float d = min(dl, dr);

    int mid = (start + end) / 2;
    for (int i = mid + 1; i <= end && dots[i].first - dots[mid].first < d; ++i) {
        float dis = getDistance(dots[i].first, dots[i].second, dots[mid].first, dots[mid].second);
        if (dis < d)
            d = dis;
    }
    for (int i = mid - 1; i >= start && dots[mid].first - dots[i].first < d; --i) {
        float dis = getDistance(dots[i].first, dots[i].second, dots[mid].first, dots[mid].second);
        if (dis < d)
            d = dis;
    }
    return d;
}

float findMin(vector<pair<int, int>>& dots) {
    sort(dots.begin(), dots.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
        });
    return help(dots, 0, dots.size() - 1);
}

int main() {
    int n = 0, min = 0;
    cin >> n;
    vector<pair<int, int>> dots(n, pair<int, int>(0, 0));
    for (size_t i = 0; i < n; i++)
    {
        int m, n;
        cin >> m >> n;
        dots[i] = pair<int, int>(m, n);
    }
    cout << findMin(dots);
    return 0;
}

// {{12,5},{23,1},{3,27},{65,4},{2,5}}
/*
5 12 5 23 1 3 27 65 4 2 5
10
22 32
28 100
29 63
65 94
119 29
108 75
7 30
108 85
105 93
6 9
*/