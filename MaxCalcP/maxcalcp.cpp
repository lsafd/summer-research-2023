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

	// Return the maximum value without restrictions
	return arr[m][n];
}

void perm_chain_construct (string X, int l, int r, Node* chain_start, int n, int k) {
 	// Base case	
	if (l == r) {
		// Add node to chain for each permutation within distance of idenitiy
		if (n - lcs(chain_start->perm, X, n, n) <= k) {
			Node* new_node = new Node();
			new_node->perm = X;
			Node* temp = chain_start->next;
			chain_start->next = new_node;
			new_node->next = temp;
		}
	}
	// For each start of the rest of the word permute the remaining part of the word with that start
	else {
		for (int i = l; i <= r; i++) {
			swap(X[l], X[i]);

			perm_chain_construct(X, l + 1, r, chain_start, n, k);

			swap(X[l], X[i]);
		}
	}
}

void perm_count (Node* chain_start, int n, int k, int set_size, int* count) {
	// head1 one iterates selected element
	Node* head1 = chain_start->next;
	
	while (true) {
		// head2 is used to find which elements can be added at the next step
		Node* head2 = head1;
	
		// Create chain to pass to next step
		Node* next_chain_start = new Node();
		next_chain_start->next = NULL;
		while (true) {
			if (head2->next == NULL) {
				break;
			}

			head2 = head2->next;

			if (n - lcs(head1->perm, head2->perm, n, n) <= k) {
				Node* new_node = new Node();
				new_node->perm = head2->perm;
				Node* temp = next_chain_start->next;
				next_chain_start->next = new_node;
				new_node->next = temp;
			}
		}

		// If there is nothing that can be added then no need to recurse
		if (next_chain_start->next == NULL) {
			// If the new set is larger then update largest size
			if (set_size + 1 > *count) {
				*count = set_size + 1;
			}
		}
		else {
			perm_count(next_chain_start, n, k, set_size + 1, count);
		}
		// Free allocated chain
		while (next_chain_start->next != NULL) {
			Node* temp = next_chain_start;
			next_chain_start = next_chain_start->next;
			delete temp;
		}
		delete next_chain_start;

		// Ensure we do not follow a null pointer
		if (head1->next == NULL) {
			break;
		}
		head1 = head1->next;
	}
}	

int main(int argc, char* argv[]) {
	// Initalize variables
	int n;
	int k;
	string to_permute;
	int count = 0;
	Node* base_start = new Node();
	base_start->next = NULL;

	// Take input
	// cout << "n: ";
	// cin >> n;
	// cout << "k: ";
	// cin >> k;
	

	// Take input from command line 
	if (argc != 3) {
		cout << "Usage: ./maxcalcp n k" << endl;
		return 0;
	}
	n = atoi(argv[1]);
	k = atoi(argv[2]);

	// Create sequence to be permuted
	for (int i = 1; i <= n; i++) {
		to_permute += to_string(i);
	}
	base_start->perm = to_permute;
	
	// Call function to create first permuatation chain
	perm_chain_construct(to_permute, 0, n - 1, base_start, n, k);
	
	// Call function to calculate max set size
	perm_count(base_start, n, k, 0, &count);

	// Free allocated chain of all permuatations
	while (base_start->next != NULL) {
		Node* temp = base_start;
		base_start = base_start->next;
		delete temp;
	}
	delete base_start;

	// Output final counts
	cout << "f_{k}(n): " << count << endl;

	return 0;

}


