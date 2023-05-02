#include<iostream>
#include<vector>

using namespace std;

// ���ݷ�����
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
	int m;		//m��ʾ���е��ʵĸ���
	int n;		//n��ʾ��ͬ��ĸ��������
	int k;		//k��ʾ��󹹳ɵ��ַ����ĳ���
	int ans{ 0 };	// �ܹ����ɵ������������ַ����ĸ���

	cin >> m >> n >> k;
	vector<string> words;	// ���еĵ���
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
