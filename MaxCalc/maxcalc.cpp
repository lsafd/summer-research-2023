#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

struct Node
{
  string perm;
  struct Node *next;
};


int lcs (string X, string Y, int m, int n) {
	// Initalize array to hold values as we progress
	int arr[m + 1][n + 1];

	// Fill array with longest common subsequence given restrictions
        for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0) {
				arr[i][j] = 0;
			}
			else if (X[i - 1] == Y[j - 1]) {
				arr[i][j] = 1 + arr[i-1][j-1];
			}
			else {
				arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
			}
		}
	}

	// Could print the subsequence here in n^2 time

	// Return the maximum value without restrictions
	return arr[m][n];
}

void permutation_counter (string X, int l, int r, Node* prev_node, int n, int k, int* c) {
 	// Base case	
	if (l == r) {
		int len = 1;
		int cur_dist = 0;

		Node* traverse = prev_node;

		while (true) {
			cur_dist = n - lcs(X, traverse->perm, n, n);
			if ((cur_dist > k) || stoi(X) <= stoi(traverse->perm)) {
				return;
			}
			len += 1;
			if (traverse->next == NULL){
				break;
			}
			traverse = traverse->next;
		}
			
		if (len > *c) {
			*c = len;
		}

		Node* front = new Node();
		front->perm = X;
		front->next = prev_node;

		permutation_counter(X, 0, n - 1, front, n, k, c);

		delete front;
		
	}
	// For each start of the rest of the word permute the remaining part of the word with that start
	else {
		for (int i = l; i <= r; i++) {
			swap(X[l], X[i]);

			permutation_counter(X, l + 1, r, prev_node, n, k, c);

			swap(X[l], X[i]);
		}
	}
}

int main() {
	// Initalize variable
	int n;
	int k;
	int* count;
	string to_permute;
	Node* base_node = new Node();

	*count = 1;
	cout << "n: ";
	cin >> n;
	cout << "k: ";
	cin >> k;


	// Create sequence to be permuted
	for (int i = 1; i <= n; i++) {
		to_permute += to_string(i);
	}

	base_node->perm = to_permute;
	base_node->next = NULL;
	
	// Call function to permute
	permutation_counter(to_permute, 0, n - 1, base_node, n, k, count);
	
	delete base_node;
	
	// Output final counts
	cout << "f_{k}(n): " << *count << endl;

	return 0;

}


