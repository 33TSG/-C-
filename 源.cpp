#include<stdio.h>
#include<string.h>

int vis[101][101];
int map[101][101];
int R, C;

int dp(int i, int j) {
	int max = 0;
	if (vis[i][j] > 0)
		return vis[i][j];
	if (i - 1 >= 0)
		if (map[i - 1][j] < map[i][j])
			if (max < dp(i - 1, j))
				max = dp(i - 1, j);

	if (i + 1 < R)
		if (map[i + 1][j] < map[i][j])
			if (max < dp(i + 1, j))
				max = dp(i + 1, j);

	if (j-1 >= 0) 
		if (map[i][j-1] < map[i][j])
			if (max < dp(i, j-1))
				max = dp(i, j-1);

	if (j+1 <= C) 
		if (map[i][j+1] < map[i][j])
			if (max < dp(i, j+1))
				max = dp(i, j+1);

	return vis[i][j] = max+1;
}

int main() {
	int i, j, ans, max;
	scanf_s("%d%d", &R, &C);
	for (i = 0; i < R; i++)
		for (j = 0; j < C; j++)
			scanf_s("%d", &map[i][j]);
	max = 0;
	for (i = 0; i < R; i++) {
		memset(vis[i], -1, sizeof(vis[i]));
		for (j = 0; j < C; j++) {
			ans = dp(i, j);
			if (ans > max)
				max = ans;
		}
	}
	printf("%d", max);
	return 0;
}