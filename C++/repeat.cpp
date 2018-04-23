#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){

	struct TreeNode{
		int value;
		TreeNode* left;
		TreeNode* right;
	};



	string input;
	int repeats;

	cout << "Enter a string: ";
	cin >> input;

	cout << "Enter a number: ";
	cin >> repeats;

	for(int i = 0; i < repeats; i++){
		cout << i+1 << ": " << input << endl;
	}


	double root = sqrt(repeats);

	cout << root << endl;

	return 0;
}
