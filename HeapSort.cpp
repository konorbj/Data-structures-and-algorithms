#include "stdafx.h"
#include <iostream>

using namespace std;

class List {
	public:
		List(int = 10);
		~List();
		bool isFull() const;
		int length() const;
		bool isEmpty() const;
		void makeEmpty();
		int search(int) const;
		void addItem(int);
		int deleteItem(int);
		void printList();
		void HeapSort();
	protected:
		int max;
		int last;
		int* array;
		void makeBigger();
		void SettleRoot(int, int);
		void SettleRootDescending(int root, int end);
};

List::List(int n) {
	max = n;
	last = -1;
	array = new int[max];
}

List::~List(){
	last = -1;
	delete[]array;
}

void List::makeEmpty(){
	last = -1;
}

bool List::isEmpty() const {
	return last == -1;
}

bool List::isFull() const {
	return last == max-1;
}

int List::length() const {
	return last + 1;
}

int List::search(int item) const {
	for (int i = 0; i <= last; i++) {
		if (array[i] == item)
			return i;
	}
	return -10000;
}

void List::addItem(int item) {
	if (isFull())
		makeBigger();
	array[++last] = item;
}

int List::deleteItem(int item) {
	if (!isEmpty()) {
		int k = search(item);
		if (k == -10000) {
			cout << "There is no such item in the list!\n";
			return -10000;
		}
		else {
			int returned = array[k];
			array[k] = array[last--];
			return returned;
		}
	}
	else
		cout << "List is empty! It's impossible to delete item!";
	return -10000;
}

void List::printList() {
	cout << "List contents:\n";
	if (last == -1)
		cout << "Printing failed! The list is empty.\n";
	else {
		for (int i = 0; i <= last; i++)
			cout << array[i] << " ";
		cout << endl;
	}
}

void List::makeBigger() {
	max = 2 * max;
	int* new_array = new int[max];
	for (int i = 0; i <= last; i++)
		new_array[i] = array[i];
	delete[]array;
	array = new_array;
}

void List::HeapSort() {
	for (int i = (last+1) / 2 - 1; i >= 0; i--)
		SettleRoot(last+1,i);//building a heap
	for (int i = last; i >= 0; i--) {
		swap(array[0],array[i]);//moving root to end of unsorted subarray
		SettleRoot(i,0);//calling SettleRoot for reduced heap
	}
}

//building a max-heap
void List::SettleRoot(int root, int end) {
	int largest = end;
	int l = 2*end + 1;//index of left child
	int r = 2*end + 2;//index of right child
	if (l < root && array[l] > array[largest])//checking if left child value is bigger
		largest = l;
	if (r < root && array[r] > array[largest])//checking if right child value is bigger
		largest = r;
	if (largest != end) {//recursive call of SettleRoot until the root is bigger than it`s children or its a leaf node
		swap(array[end],array[largest]);
		SettleRoot(root,largest);//recursive settling of a root of the affected subtree
	}
}

//building a min-heap
void List::SettleRootDescending(int root, int end) {
	int largest = end;
	int l = 2 * end + 1;//index of left child
	int r = 2 * end + 2;//index of right child
	if (l < root && array[l] < array[largest])//checking if left child value is less
		largest = l;
	if (r < root && array[r] < array[largest])//checking if right child value is less
		largest = r;
	if (largest != end) {//recursive call of SettleRoot until the root is less than it`s children or its a leaf node
		swap(array[end], array[largest]);
		SettleRoot(root, largest);//recursive settling of a root of the affected subtree
	}
}

struct PQNode {
	int data_priority;
	int data_value;
	struct PQNode *next;
		
	PQNode(){}

	PQNode(int dp, int dv) {
		data_priority = dp;
		data_value = dv;
		next = NULL;
	}
};

class PriorityQeueue {
	public:
		PriorityQeueue() { root = NULL; }
		void enqueue(int, int);
		int dequeueMax();
		bool isFull() const;
		bool isEmpty() const;
		int size();
		void printQueue();
	protected:
		PQNode *root;
};

bool PriorityQeueue::isFull() const{
	return false;
}

bool PriorityQeueue::isEmpty() const {
	return root == NULL ? true : false;
}

void PriorityQeueue::enqueue(int value, int priority) {
	if (!isFull()) {
		PQNode *temp, *q;
		temp = new PQNode;
		temp->data_priority = priority;
		temp->data_value = value;
		if (isEmpty() || priority < root->data_priority) {
			temp->next = root;
			root = temp;
		}
		else {
			q = root;
			while (q->next != NULL && q->next->data_priority <= priority)
				q = q->next;
			temp->next = q->next;
			q->next = temp;
		}
	}
}

int PriorityQeueue::dequeueMax() {
	if (isEmpty()) {
		cout << "Qeueue is empty!\n";
		return -10000;
	}
	else {
		int del = root->data_value;
		root = root->next;
		return del;
	}
}

int PriorityQeueue::size() {
	int count = 0;
	PQNode *temp = root;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}

void PriorityQeueue::printQueue() {
	if (isEmpty()){
		cout << "Qeueue content:\n";
		return;
	}
	PQNode *temp = root;
	while (temp != NULL) {
		cout << "Priority: " << temp->data_priority << "\tValue: " << temp->data_value << endl;
		temp = temp->next;
	}
}

int main()
{
	List list = List(8);
	list.addItem(20);
	list.addItem(10);
	list.addItem(40);
	list.addItem(25);
	list.addItem(70);
	list.printList();
	cout << endl;
	list.HeapSort();
	list.printList();
	cout << endl;
	PriorityQeueue q = PriorityQeueue();
	q.enqueue(1, 5);
	q.enqueue(5, 2);
	q.enqueue(10, 1);
	cout << q.size() << endl;
	q.printQueue();
	q.dequeueMax();
	cout << endl;
	q.printQueue();
	system("pause");
    return 0;
}