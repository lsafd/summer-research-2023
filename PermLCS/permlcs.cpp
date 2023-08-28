#include <string>
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

	// Could print the subsequence here in n^2 time

	// Return the maximum value without restrictions
	return arr[m][n];
}

int subsequence_counter (string X, int n, int k) {
	// Initalize array and variables
	int sum = 0;
	int arr[k][n];
	
	for (int i = 0; i < n; i++) {
		arr[0][i] = 1;
	}	

	// Iterate through string lengths and endpoints to find sequences of particular length
	for (int len = 1; len < k; len++) {
		for (int i = len; i < n; i++) {
			arr[len][i] = 0;
			for (int j = len - 1; j < i; j++) {
				if (int(X[j]) < int(X[i])) {
					arr[len][i] += arr[len - 1][j];
				}
			}
		}
	}
	
	// Sum number of strings of desired length
	for (int i = k - 1; i < n; i++) {
		sum += arr[k - 1][i];
	}
	return sum;
}

void permutation_counter (string X, int l, int r, string original, int n, int radius, int* c) {
 	// Base case	
	if (l == r) {
		string comp = "1234";
		int x_lcs = lcs(X, original, n, n); 
		int x_subs = subsequence_counter(X, n, n - radius); 
		if ((n - x_lcs) == radius) {
			cout << X << " " << x_lcs << " "  << x_subs << endl;
			c[0] += 1;
			c[1] += x_subs; 
		}
	}
	// For each start of the rest of the word permute the remaining part of the word with that start
	else {
		for (int i = l; i <= r; i++) {
			swap(X[l], X[i]);

			permutation_counter(X, l + 1, r, original, n, radius, c);

			swap(X[l], X[i]);
		}
	}
}

int main() {
	// Initalize variable
	int n;
	int r;
	int count[2];
	string to_permute;

	count[0] = 0;
	count[1] = 0;
	cout << "n: ";
	cin >> n;
	cout << "r: ";
	cin >> r;


	// Create sequence to be permuted
	for (int i = 1; i <= n; i++) {
		to_permute += to_string(i);
	}
	
	// Call function to permute
	permutation_counter(to_permute, 0, n - 1, to_permute, n, r, count);
	
	// Output final counts
	cout << "Permutations with LCS (n - r):      " << count[0] << endl;
        cout << "Totatl Length (n - r) Subsequences: " << count[1] << endl;

	return 0;

}


