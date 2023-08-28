#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

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

	// Return the maximum value without restrictions
	return arr[m][n];
}

void perm_chain_construct (string X, string original, int l, int r, vector<string>* base_vec, int n, int k) {
 	// Base case	
	if (l == r) {
		// Add node to chain for each permutation within distance of idenitiy
		if (n - lcs(original, X, n, n) <= k) {
			(*base_vec).push_back(X);
		}
	}
	// For each start of the rest of the word permute the remaining part of the word with that start
	else {
		for (int i = l; i <= r; i++) {
			swap(X[l], X[i]);

			perm_chain_construct(X, original, l + 1, r, base_vec, n, k);

			swap(X[l], X[i]);
		}
	}
}

void perm_count (vector<string>* vec_adds, int n, int k, int set_size, int* count) {
	string next_add;
	int size = (*vec_adds).size();
	for (int i = 0; i < size; i++) {
		next_add = (*vec_adds).back();
		(*vec_adds).pop_back();
		
		// Create chain to pass to next step
		vector<string> next_vec;
		for (int j = 0; j < size - i - 1; j++) {
			if (n - lcs(next_add, (*vec_adds)[j], n, n) <= k) {
				next_vec.push_back((*vec_adds)[j]);
			}
		}

		// If there is nothing that can be added then no need to recurse
		if (next_vec.empty()) {
			// If the new set is larger then update largest size
			if (set_size + 1 > *count) {
				*count = set_size + 1;
			}
		}
		else {
			perm_count(&next_vec, n, k, set_size + 1, count);
		}
	}
}	

int main() {
	// Initalize variables
	int n;
	int k;
	string to_permute;
	int count = 0;
	vector<string> base_vec;

	// Take input
	cout << "n: ";
	cin >> n;
	cout << "k: ";
	cin >> k;

	// Create sequence to be permuted
	for (int i = 1; i <= n; i++) {
		to_permute += to_string(i);
	}

	// Call function to create first permuatation chain
	perm_chain_construct(to_permute, to_permute, 0, n - 1, &base_vec, n, k);

	// Call function to calculate max set size
	perm_count(&base_vec, n, k, 0, &count);

	// Output final counts
	cout << "f_{k}(n): " << count << endl;

	return 0;

}


