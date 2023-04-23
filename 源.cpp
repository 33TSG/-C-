#include <stdio.h>
#include <string.h>

int vis[101][101];
int map[101][101];
int R, C;

int dfs(int i, int j) {
    if (vis[i][j] > 0) {
        return vis[i][j];
    }

    int max = 1;

    if (i - 1 >= 0 && map[i - 1][j] < map[i][j]) {
        int tmp = dfs(i - 1, j) + 1;
        max = tmp > max ? tmp : max;
    }

    if (i + 1 < R && map[i + 1][j] < map[i][j]) {
        int tmp = dfs(i + 1, j) + 1;
        max = tmp > max ? tmp : max;
    }

    if (j - 1 >= 0 && map[i][j - 1] < map[i][j]) {
        int tmp = dfs(i, j - 1) + 1;
        max = tmp > max ? tmp : max;
    }

    if (j + 1 < C && map[i][j + 1] < map[i][j]) {
        int tmp = dfs(i, j + 1) + 1;
        max = tmp > max ? tmp : max;
    }

    vis[i][j] = max;

    return max;
}

int main() {
    int i, j, ans, max;
    scanf_s("%d %d", &R, &C);

    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            scanf_s("%d", &map[i][j]);
        }
    }

    max = 1;

    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            ans = dfs(i, j);
            max = ans > max ? ans : max;
        }
    }

    printf("%d", max);

    return 0;
}
