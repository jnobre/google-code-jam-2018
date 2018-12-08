#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#define MAXN 2000
#define MAXL 10
//#define DEBUGLINE

using namespace std;

int n, l;
string words[MAXN];

bool hist[MAXL][26];
int tries = 0;
string result;

bool go(int k, string& curr) {
	if( k == l ) { //base case
		if(binary_search(words, words + n, curr)) {
			tries++;
			return false;
		} else {
			result = curr;
			return true;
		}
	}

	for(int i = 0 ; i < 26 ; i++) {
		if( !hist[k][i] )
			continue;
		curr.push_back((char) ('A' + i));

		
		
		if(go(k + 1, curr)) 
			return true;

		if(tries > n) 
			return false;
		curr.pop_back();
	}
	return false;
}

int main() {
	
	int t;
	scanf("%d\n", &t);

	for(int tc = 1; tc <= t ; tc++) {
		scanf("%d %d\n", &n, &l);
		for(int i = 0 ; i < n ; i++){
			cin >> words[i];
		}

		memset(hist, false, sizeof(hist));

		for(int i = 0 ; i < n ; i++) {
			for(int j = 0 ; j < l ; j++) {
				hist[j][words[i][j] - 'A'] = true;
			 }
		}

		#ifdef DEBUGLINE
			printf("\n\n\n\n");
			for(int i = 0 ; i < MAXL ; i++) {
				for(int j = 0 ; j < 26 ; j++) {
					if(hist[i][j])
						printf(" 1 ");
					else
						printf(" 0 ");
				}
				printf("\n");
			}
			printf("\n");
		#endif

		sort(words, words + n);

		tries = 0;
		result = "-";
		string curr; 

		go(0, curr);

		printf("Case #%d: %s\n", tc, result.c_str());

	}
	return 0;
}
