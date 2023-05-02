#include<iostream>
#include<vector>

using namespace std;

// 回溯法求结果
void traceBack(vector<string>& words, string aim, int l, int k, int &ans) {
	if (aim.size() == k) {
		cout << aim << endl;
		ans++;
	}
	else {
		for (int i = 0; i < words.size(); i++) {
			string a = aim.substr(aim.length() - l + 1, l - 1);
			string b = words[i].substr(0, l - 1);
			if (a == b) {
				aim += words[i][l-1];
				traceBack(words, aim, l, k, ans);
				aim.pop_back();
			}
		}
	}
}

int main() { 
	int m;		//m表示表中单词的个数
	int n;		//n表示不同字母的最大个数
	int k;		//k表示最后构成的字符串的长度
	int ans{ 0 };	// 能够构成的满足条件的字符串的个数

	cin >> m >> n >> k;
	vector<string> words;	// 所有的单词
	for (size_t i = 0; i < m; i++)
	{	
		string s;
		cin >> s;
		words.push_back(s);
	}

	for (size_t i = 0; i < words.size(); i++)
	{
		traceBack(words, words[i], words[i].size(), k, ans);
	}

	cout << ans;

	return 0;
}
