#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define Max 110

int n1, n2, m, t;
int match[Max][Max], f[Max][Max], g[Max][Max];
int s1[Max], s2[Max];

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int i, j, k;
	int ii, jj;
	scanf_s("%d", &m);
	while (m) {
		m--;
		scanf_s("%d %d", &n1, &n2);
		for (i = 1; i <= n1; i++)
			scanf_s("%d", &s1[i]);
		for (i = 1; i <= n2; i++)
			scanf_s("%d", &s2[i]);
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		for (i = 1; i <= n1; i++) {
			for (j = 1; j <= n2; j++) {
				if (s1[i] == s2[j - 1])
					f[i][j] = j - 1;
				else 
					f[i][j] = f[i][j-1];
			}
		}
		for (i = 1; i <= n2; i++) {
			for (j = 1; j <= n1; j++) {
				if (s2[i] == s1[j - 1])
					g[i][j] = j - 1;
				else
					g[i][j] = g[i][j - 1];
			}
		}
		memset(match, 0, sizeof(match));
		for (i = 1; i <= n1; i++) {
			for (j = 1; j <= n2; j++) {
				match[i][j] = max(match[i][j-1], match[i-1][j]);
				if (s1[i] == s2[j])
					continue;
				ii = f[i][j];
				jj = g[j][i];
				if (ii == 0 || jj == 0)
					continue;
				match[i][j] = max(match[i][j], match[jj-1][ii-1]+2);
			}
		}
		printf("%d", match[n1][n2]);
	}
	return 0;
}