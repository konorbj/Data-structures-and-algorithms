#include "stdafx.h"
#include <iostream>

using namespace std;

class TNode
{
	public:
		int data;
		TNode *left;
		TNode *right;
		int height;
		TNode() {}
		TNode(int d) { data = d; height = 1; left = NULL; right = NULL; }
};

class BinaryTree {
	public:
		BinaryTree() { root = NULL; }
		bool isEmpty() { return root == NULL; }
		bool isFull() { return false; }
		void preorder();
		void inorder();
		void postorder();
		void makeEmpty();
		int size() { return size_rec(root); }
		int countLeft() { return count_rec(root); }
		/*additional
		int countLeft() { return countLeft_rec(root); }
		bool isBalanced() { return isBalanced_rec(root); }*/
	protected:
		TNode *root;
		void preorder_rec(TNode *p);
		void inorder_rec(TNode *p);
		void postorder_rec(TNode *p);
		int size_rec(TNode *p);
		void makeEmpty_rec(TNode *p);
		int max(int a, int b);
		int height(TNode *p);
		int count_rec(TNode *p);
		/*additional
		int countLeft_rec(TNode *p);
		bool isBalanced_rec(TNode *p);*/
};

void BinaryTree::preorder()
{
	cout << "Preorder traversal: \n";
	if (root == NULL)
		cout << "Tree is empty.\n";
	else {
		preorder_rec(root);
		cout << ";\n";
	}
}

void BinaryTree::preorder_rec(TNode *p)
{
	if (p != NULL)
	{
		cout << p->data << " ";
		preorder_rec(p->left);
		preorder_rec(p->right);
	}
}

void BinaryTree::inorder()
{
	cout << "Inorder traversal: \n";
	if (root == NULL)
		cout << "Tree is empty.\n";
	else {
		inorder_rec(root);
		cout << ";\n";
	}
}

void BinaryTree::inorder_rec(TNode *p)
{
	if (p != NULL) {
		inorder_rec(p->left);
		cout << p->data << " ";
		inorder_rec(p->right);
	} 
}

void BinaryTree::postorder()
{
	cout << "Postorder traversal: \n";
	if (root == NULL)
		cout << "Tree is empty.\n";
	else {
		postorder_rec(root);
		cout << ";\n";
	}
}

void BinaryTree::postorder_rec(TNode *p)
{
	if (p != NULL) {
		postorder_rec(p->left);
		postorder_rec(p->right);
		cout << p->data << " ";
	}
}

void BinaryTree::makeEmpty()
{
	TNode *p = root;
	makeEmpty_rec(p);
	root = NULL;
}

void BinaryTree::makeEmpty_rec(TNode *p)
{
	if (p != NULL) {
		makeEmpty_rec(p->left);
		makeEmpty_rec(p->right);
		delete p;
	} 
}

int BinaryTree::size_rec(TNode *p)
{
	if (p == NULL)	
		return 0;
	else 		
		return size_rec(p->left) + size_rec(p->right) + 1;
}

int BinaryTree::max(int a, int b) {
	return a > b ? a : b;
}

int BinaryTree::height(TNode *p) {
	if (p == NULL)
		return 0;
	return p->height;
}

int BinaryTree::count_rec(TNode *p) {
	if (p == NULL)
		return 0;
	if (p->left == NULL)
		return count_rec(p->left);
	else
		return count_rec(p->left) + count_rec(p->right) + 1;
}

/*additional

int BinaryTree::countLeft_rec(TNode *p) {
	if (p == NULL)
		return 0;
	if (p->left == NULL)
		return countLeft_rec(p->left);
	else
		return countLeft_rec(p->left) + countLeft_rec(p->right) + 1;
}

bool BinaryTree::isBalanced_rec(TNode *p) {
	int lh, rh;
	if (p == NULL)
		return true;
	lh = height(p->left);
	rh = height(p->right);
	if (abs(lh - rh) <= 1 && isBalanced_rec(p->left) && isBalanced_rec(p->right))
		return true;
	return false;
}*/

class BBST : public BinaryTree {
	public:
		BBST() : BinaryTree() {}
		bool search(int item);
		void addNode(int item);
		void deleteNode(int item);
		bool equalBBST(BBST *tree) { if (tree->root == NULL && root) return false; if (root == NULL && tree->root) return false; if (tree->size() != size()) return false; return isEqual_rec(root, tree->root); }
		/*additional
		BBST createSymmetry() { if (!isEmpty()) { BBST tree; tree.root = new TNode(root->data); tree.root->left = root->right; tree.root->right = root->left; return tree; } }
		int fatherNode(int item);
		int secondLargest();
		void printSorted();
		bool symmetricalTrees(BBST *tree) { return symmetricalTrees_rec(root, tree->root); }
		int commonLowestAncestor(int a, int b);
		int sum() { return sum_rec(root); }
		BBST copy();
		void removeDuplicates();
		int findMiddle();
		void deleteEven();*/
	protected:
		bool search_rec(int item, TNode *p);
		TNode* addNode_rec(int item, TNode *p);
		TNode* deleteNode_rec(int item, TNode *p);
		TNode* rotateRight(TNode *p);
		TNode* rotateLeft(TNode *p);
		TNode* minNode(TNode *p);
		int getBalance(TNode *p);
		bool isEqual_rec(TNode *p, TNode *p1);
		/*additional
		TNode* fatherNode_rec(int item, TNode *p);
		TNode* secondLagrest_rec(TNode *p, int &count);
		void ascPrint(TNode *p);
		void desPrint(TNode *p);
		bool symmetricalTrees_rec(TNode *p, TNode *p1);
		int commonLowestAncestor_rec(int a, int b, TNode *p);
		int sum_rec(TNode *p);
		TNode* copy_rec(TNode *p);
		void removeDuplicates_rec(TNode *p);
		TNode* findMiddle_rec(int value, TNode *p);
		void deleteEven_rec(TNode *p);*/
};

bool BBST::search(int item)
{
	return search_rec(item, root);
}

bool BBST::search_rec(int item, TNode *p)
{
	if (p == NULL)		
		return false;
	if (p->data == item)	
		return true;
	else if (p->data > item)	 
		return search_rec(item, p->left);
	else   			
		return search_rec(item, p->right);
}

void BBST::addNode(int item)
{
	root = addNode_rec(item, root);
}

void BBST::deleteNode(int item) {
	if (search(item)) {
		root = deleteNode_rec(item,root);
	}
	else {
		cout << "There is no " << item << "element. It can't be deleted!\n";
	}
}

TNode* BBST::addNode_rec(int item, TNode *p) {
	if (p == NULL)
		return new TNode(item);

	if (item < p->data)
		p->left = addNode_rec(item, p->left);
	else
		p->right = addNode_rec(item,p->right);

	p->height = 1 + max(height(p->left),height(p->right));

	int balance = getBalance(p);

	if (balance > 1 && item < p->left->data)
		return rotateRight(p);

	if (balance < -1 && item > p->right->data)
		return rotateLeft(p);

	if (balance > 1 && item > p->left->data)
	{
		p->left = rotateLeft(p->left);
		return rotateRight(p);
	}

	if (balance < -1 && item < p->right->data)
	{
		p->right = rotateRight(p->right);
		return rotateLeft(p);
	}

	return p;
}

TNode* BBST::deleteNode_rec(int item, TNode *p) {
	if (p == NULL)
		return p;
	
	if (item < p->data)
		p->left = deleteNode_rec(item, p->left);
	else if (item > p->data)
		p->right = deleteNode_rec(item, p->right);
	else
	{
		if (p->left == NULL || root->right == NULL)
		{
			TNode *temp = p->left ? p->left : p->right;
			if (temp == NULL)
			{
				temp = p;
				p = NULL;
			}
			else
				*p = *temp;
			delete temp;
		}
		else
		{
			TNode *temp = minNode(p->right);
			p->data = temp->data;
			p->right = deleteNode_rec(temp->data,p->right);
		}
	}
	
	if (p == NULL)
		return p;

	p->height = 1 + max(height(p->left),height(p->right));
	int balance = getBalance(p);

	if (balance > 1 && getBalance(p->left) >= 0)
		return rotateRight(p);
	if (balance > 1 && getBalance(p->left) < 0)
	{
		p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	if (balance < -1 && getBalance(p->right) <= 0)
		return rotateLeft(p);
	if (balance < -1 && getBalance(p->right) > 0)
	{
		p->right = rotateRight(p->right);
		return rotateLeft(p);
	}

	return p;
}

TNode* BBST::rotateRight(TNode *p) {
	TNode *temp = p->left;
	TNode *temp2 = temp->right;

	temp->right = p;
	p->left = temp2;

	p->height = max(height(p->left), height(p->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;

	return temp;
}

TNode* BBST::rotateLeft(TNode *p) {
	TNode *temp = p->right;
	TNode *temp2 = temp->left;

	temp->left = p;
	p->right = temp2;

	p->height = max(height(p->left), height(p->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;

	return temp;
}

TNode* BBST::minNode(TNode *p) {
	TNode *current = p;

	while (current->left != NULL)
		current = current->left;

	return current;
}

int BBST::getBalance(TNode *p)
{
	if (p == NULL)
		return 0;
	return height(p->left) - height(p->right);
}

bool BBST::isEqual_rec(TNode *p, TNode *p1) {
	bool res1 = true;
	bool res2 = true;
	if (p != NULL && p1 != NULL) {
		if (p->data != p1->data)
			return false;
		else {
			res1 = isEqual_rec(p->left, p1->left);
			res2 = isEqual_rec(p->right, p1->right);
		}
	}
	if (res1 == true && res2 == true)
		return true;
	else
		return false;
}

/*additional

int BBST::fatherNode(int item) {
	if (search(item)) {
		TNode *p = fatherNode_rec(item, root);
		if (p == NULL)
			return -10000;
		else
			return p->data;
	}
	else
		return -10000;
}

TNode* BBST::fatherNode_rec(int item, TNode *p) {
	if (p == NULL)
		return NULL;

	if (p->left == NULL && p->right == NULL)
		return NULL;

	if (p->left != NULL && p->left->data == item || p->right != NULL && p->right->data == item)
		return p;

	if (p->data > item)
		return fatherNode_rec(item,p->left);

	if (p->data < item)
		return fatherNode_rec(item,p->right);
}

int BBST::secondLargest() {
	if (!isEmpty()) {
		int count = 0;
		return secondLagrest_rec(root,count).data;
	}
}

TNode* BBST::secondLagrest_rec(TNode *p, int &count) {
	if (p == NULL || count >= 2)
		return NULL;
	secondLagrest_rec(p->right, count);
	count++;
	if (count == 2)
	{
		return p;
	}
	secondLagrest_rec(p->left, count);
}

void BBST::printSorted() {
	cout << "Ascending order: \n";
	ascPrint(root);
	cout << ";\n";
	cout << "Descending order: \n";
	desPrint(root);
	cout << ";\n";
}

void BBST::ascPrint(TNode *p) {
	if (p != NULL) {
		ascPrint(p->left);
		cout << p->data << " ";
		ascPrint(p->right);
	}
}

void BBST::desPrint(TNode *p) {
	if (p != NULL) {
		desPrint(p->right);
		cout << p->data << " ";
		ascPrint(p->left);
	}
}

bool BBST::symmetricalTrees_rec(TNode *p, TNode *p1) {
	if (p == NULL && p1 == NULL)
		return true;
	if (p == NULL && p1 != NULL || p != NULL && p1 == NULL)
		return false;
	return symmetricalTrees_rec(p->left,p1->left) && symmetricalTrees_rec(p->right,p1->right);
}



int BBST::commonLowestAncestor(int a, int b) {
	if (search(a) && search(b))
		return commonLowestAncestor_rec(a, b, root);
	else
		return -10000;
}

int BBST::commonLowestAncestor_rec(int a, int b, TNode *p){
	if (p == NULL)
		return -10000;
	if (p->data > a && p->data > b)
		return commonLowestAncestor_rec(a,b,p->left);
	if (p->data < a && p->data < b)
		return commonLowestAncestor_rec(a, b, p->right);
	return p->data;
}

int BBST::sum_rec(TNode *p) {
	int sum = 0;
	if (p->left != NULL)
		sum += sum_rec(p->left);
	if (p->right != NULL)
		sum += p->right->data + sum_rec(p->right);
	return sum;
}

BBST BBST::copy() {
	BBST tree;
	tree.root = copy_rec(root);
	return tree;
}

TNode* BBST::copy_rec(TNode *p) {
	if (p == NULL)
		return p;
	TNode *temp = new TNode();
	temp->data = p->data;
	temp->left = copy_rec(p->left);
	temp->right = copy_rec(p->right);
	return temp;
}

void BBST::removeDuplicates() {
	removeDuplicates_rec(root);
}

void BBST::removeDuplicates_rec(TNode *p) {
	if (p != NULL) {
		if (p->right != NULL) {
			if (p->data == p->right->data) {
				root = deleteNode_rec(p->data, root);
				removeDuplicates_rec(p);
			}
		}
		removeDuplicates_rec(p->left);
		removeDuplicates_rec(p->right);
	}
}

int BBST::findMiddle() {
	int min = 0, max = 0, middle = 0;
	TNode *p = root;
	while (p->left != NULL)
		p = p->left;
	min = p->data;
	p = root;
	while (p->right != NULL)
		p = p->right;
	max = p->data;
	middle = abs((min + max) / 2);
	p = findMiddle_rec(middle, root);
	if (p != NULL) {
		middle = p->data;
		delete p;
		return middle;
	}
	else {
		return -10000;
	}
}

TNode* BBST::findMiddle_rec(int value, TNode *p) {
	if (p != NULL) {
		if (p->left != NULL && abs(value - p->left->data) < abs(value - p->data))
			p->left = findMiddle_rec(value, p->left);
		else if (p->right != NULL && abs(value - p->right->data) < abs(value - p->data))
			p->right = findMiddle_rec(value, p->right);
		else
			return p;
	}
	else {
		return NULL;
	}
}

void BBST::deleteEven() {
	deleteEven_rec(root);
}

void BBST::deleteEven_rec(TNode *p) {
	if (p != NULL) {
		
	}
}*/

int main()
{
	BBST tree;
	tree.addNode(15);
	tree.addNode(10);
	tree.addNode(77);
	tree.addNode(60);
	tree.addNode(12);
	tree.addNode(11);
	tree.addNode(45);
	tree.addNode(13);
	tree.addNode(25);
	tree.addNode(14);
	tree.addNode(10);
	tree.preorder();
	cout << tree.countLeft() << endl;
	/*tree.preorder();
	tree.inorder();
	tree.postorder();
	tree.addNode(25);
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << "Size: " << tree.size() << "\n";
	tree.addNode(17);
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << "Size: " << tree.size() << "\n";
	tree.addNode(35);
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << "Size: " << tree.size() << "\n";
	tree.addNode(30);
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << "Size: " << tree.size() << "\n";
	tree.addNode(40);
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << "Size: " << tree.size() << "\n";
	tree.deleteNode(17);
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << tree.size() << "\n";
	tree.deleteNode(30);
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << "Size: " << tree.size() << "\n";
	cout << "Searching for 30 in BBST: \n";
	if (tree.search(30) == true)
		cout << "\tThere is 30 in this BBST.\n";
	else
		cout << "\tThere is no 30 in this BBST.\n";
	cout << "Searching for 35 in BBST: \n";
	if (tree.search(35) == true)
		cout << "\tThere is 35 in this BBST.\n";
	else
		cout << "\tThere is no 35 in this BBST.\n";
	tree.makeEmpty();
	cout << "Making the tree empty: \n";
	tree.preorder();
	tree.inorder();
	tree.postorder();
	cout << "Size: " << tree.size() << "\n";*/
	system("pause");
    return 0;
}