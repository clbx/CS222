#include <iostream>
#include <string>
#include <cmath>

using namespace std;


struct TreeNode{
	int value;
	TreeNode* left;
	TreeNode* right;
};

void insert(TreeNode* &root, int data){
	if(root == NULL){
		root = new TreeNode();
		root->value = data;
		root->right = NULL;
		root->left = NULL;
	}
	else if( data < root->value)
		insert(root->left, data);
	else if(data > root->value)
		insert(root->right, data);
	else{

	}

}


void inorder(TreeNode* root){
	if(root != NULL){
		inorder(root->left);
		cout << root->value << endl;
		inorder (root->right);
	}
}

void cleanUp(TreeNode* root){
	cleanUp(root->left);
	cleanUp(root->right);
	delete root;
	root = NULL;
}


int main(){
	TreeNode* root = NULL;
	int numbers;
	cout << "How many numbers do you want: ";
	cin >> numbers;

	for(int i = 0; i < numbers; i++){
		int add;
		cout << "Enter Number " << i+1 <<": ";
		cin >> add;
		insert(root, add);

	}

	inorder(root);
	cleanUp(root);

	return 0;
}
