#include <cstdio>
#include <cstring>

#define MAXR 100
#define MAXC 100

int r, c, h, v;
bool matrix[MAXR][MAXC];

int chips, cutsH[MAXR], counterH[MAXR];

bool solve() {
  if(chips == 0) 
  	return true;
  if(chips % ((h + 1) * (v + 1)) != 0) 
  	return false;

  memset(cutsH, 0, sizeof(cutsH));
  int target = chips / (h + 1);
  for(int i = 0, k = 0, cnt = 0; i < r; i++) {
    for(int j = 0; j < c; j++) cnt += matrix[i][j];
    cutsH[i] = k;

    if(cnt > (k + 1) * target) 
    	return false;
    if(cnt == (k + 1) * target) 
    	k++;
  }

  memset(counterH, 0, sizeof(counterH));
  target = chips / ((h + 1) * (v + 1));
  for(int j = 0, k = 0; j < c; j++) {
    for(int i = 0; i < r; i++) counterH[cutsH[i]] += matrix[i][j];

    int partCnt = 0;
    for(int i = 0; i < h + 1; i++) {
      if(counterH[i] > (k + 1) * target) 
      	return false;
      if(counterH[i] == (k + 1) * target) 
      	partCnt++;
    }
    if(partCnt == h + 1) 
    	k++;
  }
  return true;
}

int main() {
  int t; scanf("%d\n", &t);
  for(int tc = 1; tc <= t; tc++) {
    scanf("%d %d %d %d\n", &r, &c, &h, &v);
    chips = 0;
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        char ch; scanf("%c", &ch);
        matrix[i][j] = ch == '@';
        chips += ch == '@';
      }
      scanf("\n");
    }
    printf("Case #%d: %s\n", tc, solve() ? "POSSIBLE" : "IMPOSSIBLE");
  }
  return 0;
}

