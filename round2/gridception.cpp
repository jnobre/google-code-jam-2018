#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
using namespace std;


typedef long long ll;
typedef pair<int, int> pii;
#define mp make_pair

const int N = 23;
char s[N];
int a[N][N];
bool g[N][N];
bool used[N][N];
int sz;
int n, m;
int ANS;

const int DX[] = {1, 0, -1, 0};
const int DY[] = {0, 1, 0, -1};

bool checkHave(int X, int Y, int mask) {
	X = min(X, 1);
	Y = min(Y, 1);
	for (int x = 0; x < n; x++)
		for (int y = 0; y < m; y++) {
			bool ok = true;
			for (int dx = 0; dx < 2; dx++)
				for (int dy = 0; dy < 2; dy++) {
					if (X == 0 && dx == 1) continue;
					if (Y == 0 && dy == 1) continue;
					if (x == 0 && dx == 1) {
						ok = false;
						continue;
					}
					if (y == 0 && dy == 1) {
						ok = false;
						continue;
					}
					int z = 2 * dy + dx;
					int col = (mask >> z) & 1;
					ok &= a[x - dx][y - dy] == col;
				}
			if (ok) return true;
		}
	return false;
}

bool checkCell(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m && g[x][y];
}

void dfs(int x, int y) {
	sz++;
	used[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int xx = x + DX[i], yy = y + DY[i];
		if (!checkCell(xx, yy)) continue;
		if (used[xx][yy]) continue;
		dfs(xx, yy);
	}
}

int solve() {
	ANS = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		for (int j = 0; j < m; j++)
			a[i][j] = (s[j] == 'B' ? 0 : 1);
	}
	for (int x = 0; x < n; x++)
		for (int y = 0; y < m; y++)
			for (int mask = 0; mask < 16; mask++) {
				if (!checkHave(x, y, mask)) continue;
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++) {
						int z = 0;
						if (i < x) z |= 1;
						if (j < y) z |= 2;
						int col = (mask >> z) & 1;
						g[i][j] = a[i][j] == col;
					}
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++)
						used[i][j] = 0;
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++) {
						if (used[i][j] || !g[i][j]) continue;
						sz = 0;
						dfs(i, j);
						ANS = max(ANS, sz);
					}
			}
	return ANS;
}

int main()
{

	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: %d\n", i, solve());
	}

	return 0;
}