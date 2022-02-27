#include<iostream>
#include<algorithm>
using namespace std;

struct Trie {
	Trie* next[10];
	bool finish;
	bool nextChild;

	Trie() {
		fill(next, next + 10, nullptr);
		finish = nextChild = false;
	}

	~Trie() {
		for (int i = 0; i < 10; i++) {
			if (next[i])
				delete next[i];
		}
	}

	void insert(char* key) {
		if (*key == '\0') {
			finish = true;
		}
		else {
			int now = *key - '0';

			if (next[now] == NULL)
				next[now] = new Trie();
			nextChild = true;

			next[now]->insert(key + 1);
		}
	}

	bool find(char* key) {
		if (*key == '\0')
			return 0;
		if (finish)
			return 1;
		int now = *key - '0';
		return next[now]->find(key + 1);
	}
};

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int t; cin >> t;
	while (t--)	{
		int n; cin >> n;
		char arr[10001][11];
		Trie* root = new Trie();

		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			root->insert(arr[i]);
		}
		bool tmp = false;
		for (int i = 0; i < n; i++) {
			if (root->find(arr[i]))
				tmp = true;
		}
		tmp ? cout << "NO\n" : cout << "YES\n";
		delete root;
	}
	return 0;
}