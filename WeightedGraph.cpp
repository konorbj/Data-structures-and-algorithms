#include "stdafx.h"
#include <iostream>

using namespace std;

struct EDGE 
{
	public:
		int vertex1;
		int vertex2;
		int weight;
		EDGE* next;

		EDGE(int v1, int v2, int w) 
		{
			vertex1 = v1;
			vertex2 = v2;
			weight = w;
			next = NULL;
		}
};

typedef EDGE* EDGE_PTR;

struct Node {
	int v1;
	int v2;
	int weight;
	Node *next;
	Node() { next = NULL; }
	Node(int w, int v, int V, Node *link = NULL) { weight = w; v1 = v; v2 = V; next = link; }
};

class LinkedList{
	public:
		LinkedList();
		~LinkedList();
		bool isEmpty();
		void addItem(int,int,int);
		Node* Head() { return head; }
		Node* getMinValue();
		void makeEmpty() {
			while (head != NULL) { head = head->next; }
		}
		Node* pop() { Node* h = head; head = head->next; return h; }
	protected:
		Node *head;
};

Node* LinkedList::getMinValue() {
	Node *temp = head, *min_prev = NULL, *prev = NULL, *res = new Node(INT_MAX,1,1);
	while (temp != NULL) {
		if (temp->weight < res->weight) {
			min_prev = prev;
			res = temp;
		}
		prev = temp;
		temp = temp->next;
	}
	if (head == res) {
		head = head->next;
		return res;
	}
	else {
		min_prev->next = res->next;
		return res;
	}
}

bool LinkedList::isEmpty()
{
	return head == NULL;	
}

LinkedList::LinkedList()
{
	head = NULL;
}

LinkedList::~LinkedList()
{
	Node *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void LinkedList::addItem(int w, int v, int v2)
{
	head = new Node(w, v, v2, head);
}

class GraphWeighted 
{
	public:
		GraphWeighted ();
		~GraphWeighted ();
		int Nodes_number();
		int Edges_number();
		void printGraph();
		void Kruskul();
		void Dijkstra(int,int);
		int** MST_Prim_SAR_ADJ(int);
		void MST_Prim_ULL_MAT(int);
	private:
		int n;
		int m;
		void SP(int start);
		void AddToMST(EDGE_PTR*,int,int,int);
		EDGE_PTR* adjacencyList;
		void print_list(int i);
		void Insert_Nodes(int, int, int);
		void findTreePath(EDGE_PTR&, EDGE_PTR&, int, int);
		void insert_Fringe(EDGE_PTR&, int, int, int);
		void refactor(EDGE_PTR *list);
		void Insert_Fringe_Sorted_Array(EDGE_PTR *List, int father, int son, int weight);
};

void GraphWeighted::SP(int start) {
	if (start <= n && start > 0) {
		if (start == 1) {
			for (int i = 2; i <= n; i++)
				Dijkstra(start, i);
		}
		else if (start == n) {
			for (int i = 1; i < n; i++)
				Dijkstra(start, i);
		}
		else {
			for (int i = 1; i < start; i++)
				Dijkstra(start, i);
			for (int i = start + 1; i <= n; i++)
				Dijkstra(start, i);
		}
	}
}

GraphWeighted::GraphWeighted() {
	int edge_weight;
	int answer;

	cout << "Enter number of vertices: ";
	cin >> n;
	
	adjacencyList = new EDGE_PTR[n + 1];
	for (int i = 1; i <= n; i++)
		adjacencyList[i] = NULL;

	int edge_count = 0;
	for (int i = 1; i <= n; i++) 
	{
		cout << "\nAdjacency list for graph vertex #"<<i<<"\n";
		answer = 1;
		while (answer != -1) 
		{
			cout << "Enter number of current adjacent vertex (-1 to finish): ";
			cin >> answer;
			if (answer == -1)
				break;
			if (answer >= 1 && answer <= n)
			{
				cout << "Enter the integer weight of edge " << i << "--" << answer << ": ";
				cin >> edge_weight;
				Insert_Nodes(i, answer, edge_weight);
				edge_count++;
			}
			else
				cout << "Vertex number is out of range!\n";
		}
	}
	
	m = edge_count;
	cout << "\nAdjacency lists for each vertex of input graph:\n";
	for (int i = 1; i <= n; i++) {
		cout << "List for vertex #" << i << ":";
		print_list(i);
	}
}

GraphWeighted::~GraphWeighted()
{
	for (int i = 1; i <= n; i++)
	{
		EDGE_PTR p;
		while (adjacencyList[i] != NULL) {
			p = adjacencyList[i];
			adjacencyList[i] = adjacencyList[i]->next;
			delete p;
		}
	}
}

void GraphWeighted::print_list(int i) {
	EDGE_PTR current = adjacencyList[i];
	while (current != NULL) {
		cout << "(" << i << "--" << current->vertex2 << "|" << current->weight << "),";
		current = current->next;
	}
	cout << endl;
}

void GraphWeighted::Insert_Nodes(int start, int end, int x) {
	EDGE_PTR new_pointer, current, previous;
	current = adjacencyList[start];
	previous = NULL;
	while (current != NULL) {
		if (current->vertex2 < end) {
			previous = current;
			current = current->next;
		}
		else
			break;
	}
	new_pointer = new EDGE(start, end, x);
	if (previous == NULL) {
		new_pointer->next = adjacencyList[start];
		adjacencyList[start] = new_pointer;
	}
	else {
		new_pointer->next = current;
		previous->next = new_pointer;
	}
}

void GraphWeighted::printGraph() {
	cout << "\nAdjacency lists for each vertex of graph:\n";
	for (int i = 1; i <= n; i++) {
		cout << "List for vertex #" << i << ":";
		print_list(i);
	}
}

int GraphWeighted::Nodes_number() {
	return n;
}

int GraphWeighted::Edges_number() {
	return m;
}

void GraphWeighted::Kruskul() {
	struct EDGES {
		int vertex1;
		int vertex2;
		int weight;
	};

	EDGES* edge_list = new EDGES[m + 1];
	EDGES* MST_edges = new EDGES[n];
	int* component = new int[n + 1];
	for (int i = 1; i <= n; i++)
		component[i] = i;
	EDGE_PTR current;
	int count = 0;
	for (int i = 1; i <= n; i++) {
		current = adjacencyList[i];
		while (current != NULL) {
			if (current->vertex2 > i - 1) {
				edge_list[count].vertex1 = current->vertex1;
				edge_list[count].vertex2 = current->vertex2;
				edge_list[count].weight = current->weight;
				count++;
			}
			current = current->next;
		}
	}
	EDGES temp;
	for (int i = 1; i < count; i++) {
		temp = edge_list[i];
		int j;
		for (j = i - 1; j >= 0 && temp.weight < edge_list[j].weight; j--)
			edge_list[j + 1] = edge_list[j];
		edge_list[j + 1] = temp;
	}
	int MST_count = 1;
	for (int i = 0; i < count && MST_count < n; i++) {
		int a = edge_list[i].vertex1;
		int b = edge_list[i].vertex2;
		if (component[a] != component[b]) {
			MST_edges[MST_count] = edge_list[i];
			MST_count++;
			int keep = component[b];
			for (int j = 1; j <= n; j++) {
				if (component[j] == keep)
					component[j] = component[a];
			}
		}
	}
	cout << "List of edges in MST Kruskal:\n";
	for (int i = 1; i < n; i++)
		cout << MST_edges[i].vertex1 << "," << MST_edges[i].vertex2 << " edge weight: " << MST_edges[i].weight << "\n";
	delete[]component;
	delete[]edge_list;
	delete[]MST_edges;
}

void GraphWeighted::Dijkstra(int start, int end) {
	int father, son, length;
	EDGE_PTR fringe_pointer = NULL, tree_pointer = NULL, SP_pointer = NULL;
	char* marks_status = new char[n + 1];
	for (int i = 1; i <= n; i++)
		marks_status[i] = 'u';
	int* distance = new int[n + 1];
	for (int i = 1; i <= n; i++)
		distance[i] = 0;
	EDGE_PTR current = adjacencyList[start];
	marks_status[start] = 't';
	while (current != NULL) {
		father = current->vertex1;
		son = current->vertex2;
		length = (current->weight) + distance[start];
		insert_Fringe(fringe_pointer, father, son, length);
		marks_status[son] = 'f';
		current = current->next;
	}
	while (fringe_pointer != NULL){
		EDGE_PTR new_SPT_edge = fringe_pointer;
		fringe_pointer = fringe_pointer->next;
		new_SPT_edge->next = tree_pointer;
		tree_pointer = new_SPT_edge;
		marks_status[new_SPT_edge->vertex2] = 't';
		distance[new_SPT_edge->vertex2] = new_SPT_edge->weight;
		current = adjacencyList[new_SPT_edge->vertex2];
		while (current != NULL) {
			if (marks_status[current->vertex2] != 't') {
				father = current->vertex1;
				son = current->vertex2;
				length = current->weight + distance[new_SPT_edge->vertex2];
				insert_Fringe(fringe_pointer, father, son, length);
				marks_status[son] = 'f';
			}
			current = current->next;
		}
	}
	cout << "List of edges in SP tree:\n";
	EDGE_PTR temp = tree_pointer;
	while (temp != NULL) {
		cout << "(" << temp->vertex1 << "," << temp->vertex2 << ") distance from start vertex to vertex " << temp->vertex2 << ":" << temp->weight << "\n";
		temp = temp->next;
	}
	findTreePath(SP_pointer, tree_pointer, start, end);
	cout << "Edges in shortest path from vertex: " << start << " to vertex " << end << "\n";
	temp = SP_pointer;
	while (temp != NULL) {
		cout << "(" << temp->vertex1 << "," << temp->vertex2 << ") distance from start vertex to vertex " << temp->vertex2 << ":" << temp->weight << "\n";
		temp = temp->next;
	}
	delete[]marks_status;
	delete[]distance;
	while (tree_pointer != NULL) {
		temp = tree_pointer;
		tree_pointer = tree_pointer->next;
		delete temp;
	}
	while (SP_pointer != NULL) {
		temp = SP_pointer;
		SP_pointer = SP_pointer->next;
		delete temp;
	}
}

void GraphWeighted::insert_Fringe(EDGE_PTR &list, int start, int end, int x) {
	EDGE_PTR ptr, previous = NULL, current = list;
	int insert_search = 0;
	while (current != NULL && current->weight < x && current->vertex2 != end) {
		previous = current;
		current = current->next;
	}
	if (current == NULL)
		insert_search = 1;
	else {
		if (current->weight >= x)
			insert_search = 2;
	}
	if (insert_search != 0) {
		ptr = new EDGE(start, end, x);
		if (previous == NULL) {
			ptr->next = list;
			list = previous = ptr;
		}
		else {
			ptr->next = current;
			previous->next = ptr;
			previous = ptr;
		}
		if (insert_search == 2) {
			while (current != NULL && current->vertex2 != end) {
				previous = current;
				current = current->next;
			}
			if (current != NULL) {
				previous->next = current->next;
				delete current;
			}
		}
	}
}

void GraphWeighted::findTreePath(EDGE_PTR &pathPointer, EDGE_PTR &treePointer, int start, int end) {
	EDGE_PTR current, previous;
	for (int i = end; i != start; i = current->vertex1) {
		current = treePointer;
		previous = NULL;
		while (current != NULL && current->vertex2 != i) {
			previous = current;
			current = current->next;
		}
		if (previous == NULL) {
			treePointer = current->next;
		}
		else {
			previous->next = current->next;
		}
		current->next = pathPointer;
		pathPointer = current;
	}
}

int** GraphWeighted::MST_Prim_SAR_ADJ(int start) {
	int father, son, weight;
	LinkedList fringe = LinkedList();
	char* marks = new char[n + 1];
	
	for (int i = 1; i <= n; i++)
		marks[i] = 'u';
	EDGE_PTR current = adjacencyList[start];
	marks[start] = 't';
	
	while (current != NULL) {
		father = current->vertex1;
		son = current->vertex2;
		weight = current->weight;
		fringe.addItem(weight,father,son);
		marks[son] = 'f';
		current = current->next;
	}

	int** matrix = new int*[n + 1];
	for (int i = 1; i <= n; i++) {
		matrix[i] = new int[n + 1];
		for (int j = 1; j <= n; j++) {
			matrix[i][j] = INFINITY;
		}
	}

	Node *new_MST_edge;

	while (fringe.Head() != NULL) {
		new_MST_edge = fringe.getMinValue();
		matrix[new_MST_edge->v1][new_MST_edge->v2] = new_MST_edge->weight;
		marks[new_MST_edge->v2] = 't';
		current = adjacencyList[new_MST_edge->v2];
		
		while (current != NULL) {
			if (marks[current->vertex2] != 't') {
				father = current->vertex1;
				son = current->vertex2;
				weight = current->weight;
				if (new_MST_edge->v1 != father) {
					fringe.makeEmpty();
					new_MST_edge->v1 = father;
					fringe.addItem(weight, father, son);
				}
				else
					fringe.addItem(weight, father, son);
				marks[son] = 'f';
			}
			current = current->next;
		}
	}
	delete[]marks;
	fringe.~LinkedList();
	return matrix;
}

void GraphWeighted::MST_Prim_ULL_MAT(int start) {
	int father, son, weight;
	EDGE_PTR *fringe = new EDGE_PTR[n];
	EDGE_PTR* tree_pointer = new EDGE_PTR[n+1];
	char *marks = new char[n];
	for (int i = 0; i < n; i++)
	{
		marks[i] = 'u';
	}
	for (int i = 0; i < n; i++)
	{
		fringe[i] = NULL;
	}
	for (int i = 1; i <= n; i++)
		tree_pointer[i] = NULL;
	EDGE_PTR current = adjacencyList[start];
	marks[start] = 't';

	while (current != NULL)
	{
		father = current->vertex1;
		son = current->vertex2;
		weight = current->weight;
		Insert_Fringe_Sorted_Array(fringe, father, son, weight);
		marks[son] = 'f';
		current = current->next;
	}

	while (fringe[0] != NULL)
	{
		EDGE_PTR new_MST_edge = fringe[0];
		refactor(fringe);
		AddToMST(tree_pointer, new_MST_edge->vertex1, new_MST_edge->vertex2, new_MST_edge->weight);
		AddToMST(tree_pointer, new_MST_edge->vertex2, new_MST_edge->vertex1, new_MST_edge->weight);
		marks[new_MST_edge->vertex2] = 't';

		current = adjacencyList[new_MST_edge->vertex2];

		while (current != NULL)
		{
			if (marks[current->vertex2] != 't')
			{
				father = current->vertex1;
				son = current->vertex2;
				weight = current->weight;
				Insert_Fringe_Sorted_Array(fringe, father, son, weight);
				marks[son] = 'f';
			}
			current = current->next;
		}
	}

	cout << "\nList of EDGES in Prim`s MST: \n";
	for (int i = 1; i <= n; i++) {
		EDGE_PTR current = tree_pointer[i];
		while (current != NULL) {
			cout << "(" << i << "--" << current->vertex2 << "|" << current->weight << "),";
			current = current->next;
		}
		cout << endl;
	}
}

void GraphWeighted::AddToMST(EDGE_PTR* arr, int start, int end, int x) {
	EDGE_PTR new_pointer, current, previous;
	current = arr[start];
	previous = NULL;
	while (current != NULL) {
		if (current->vertex2 < end) {
			previous = current;
			current = current->next;
		}
		else
			break;
	}
	new_pointer = new EDGE(start, end, x);
	if (previous == NULL) {
		new_pointer->next = arr[start];
		arr[start] = new_pointer;
	}
	else {
		new_pointer->next = current;
		previous->next = new_pointer;
	}
}

void GraphWeighted::refactor(EDGE_PTR *list)
{
	int i;
	for (i = 0; i < n && list[i] != NULL; i++)
	{
		list[i] = list[i + 1];
	}
}

void GraphWeighted::Insert_Fringe_Sorted_Array(EDGE_PTR *List, int father, int son, int weight)
{
	EDGE_PTR newNode;
	int insert_search = 0;
	int i;
	for (i = 0; List[i] != NULL && i < n && List[i]->vertex2 != son; i++);
	if (List[i] == NULL)
	{
		insert_search = 1;
	}
	else
	{
		if (List[i]->weight >= weight)
		{
			insert_search = 2;
		}
	}
	if (insert_search != 0)
	{
		newNode = new EDGE(father, son, weight);
		if (List[i] == NULL)
		{
			List[i] = newNode;
		}
		else
		{
			int k;
			for (k = 0; List[k] != NULL && k < n; k++);
			for (int j = k; j > i; j--)
			{
				List[j] = List[j - 1];
			}
		}

		if (insert_search == 2)
		{
			for (; List[i] != NULL && List[i]->vertex2 != son; i++)
				if (List[i] != NULL)
				{
					int m;
					for (m = i; List[m] != NULL && m + 1 < n; m++)
					{
						List[m] = List[m + 1];
					}
				}
		}
	}
}

int main()
{
	GraphWeighted graph = GraphWeighted();
	//graph.MST_Prim_ULL_MAT(1);
	int i = 0;
	cin >> i;
	int** m = graph.MST_Prim_SAR_ADJ(1);
	for (int i = 1; i <= graph.Nodes_number(); i++) {
		for (int j = 1; j <= graph.Nodes_number(); j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
    return 0;
}