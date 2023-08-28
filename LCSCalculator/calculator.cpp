#include <iostream>

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

int main() {
	// Create variables
	string first_seq;
	string second_seq;	

	// Take strings
	cout << "First Sequence: ";
	cin >> first_seq;

	cout << "Second Sequence: ";
	cin >> second_seq;

        // Give output
	cout << lcs(first_seq, second_seq, first_seq.size(), second_seq.size()) << endl;
	
	return 0;

}


