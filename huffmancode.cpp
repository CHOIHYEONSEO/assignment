#include <iostream>
#include <string>
 
using namespace std;
 
 
class Node {
	friend class Minheap;
	friend class Stack;
 
private:
	int frequency;
	Node* left_child;
	Node* right_child;	
	string code;
 
};
 
class Stack {
	friend class Minheap;
 
private:
	int size;
	Node** A;
 
public:
	Stack(int s) {
		size = s;
		A = new Node * [100];
	}
 
	Node* Pop() {
		return A[size--];
	}
 
	void Push(Node* N) {
		A[++size] = N;
	}
 
	bool isempty() {
		if (size == 0)
			return true;
		return false;
	}
};
 
 
 
 
class Minheap {
private:
	int size;
	Node** A;
 
public:
	Node* CreateNode(int freq) {
		Node* temp = new Node;
		temp->frequency = freq;
		temp->left_child = temp->right_child = NULL;
		temp->code = "\n";
		return temp;
	}
 
 	void swap(Node** a, Node** b) {
		Node* temp;
		temp = *a;
		*a = *b;
		*b = temp;
	}
 
	void InitializeMinheap(int s, int* input) {
		size = s;
		A = new Node * [100];
		for (int i = 1; i <= s; i++)
			A[i] = CreateNode(input[i]);
 
		BuildMinheap();
	}
 
	void Minheapify(int i) {
		int left, right;
		int smallest = i;
 
		while (1) {
			left = i * 2;
			right = i * 2 + 1;
 
			if (left <= size && A[left]->frequency < A[i]->frequency)
				smallest = left;
			if (right <= size && A[right]->frequency < A[smallest]->frequency)
				smallest = right;
 
			if (smallest == i)
				break;
 
			swap(&A[smallest], &A[i]);
			i = smallest;
		}
	}
 
	void BuildMinheap() {
		for (int i = size / 2; i >= 1; i--) {
			Minheapify(i);
		}
	}
 
	Node* Extract_min() {
		Node* temp = A[1];
		A[1] = A[size];
		Minheapify(1);
		size--;
 
		return temp;
	}
 
	void Insert(Node* N) {
		size++;
		int i = size;
		A[i] = N;
 
		while (1) {
			if (i == 1)
				break;
			int p = i / 2;
			if (A[p]->frequency <= A[i]->frequency)
				break;
			swap(&A[p], &A[i]);
			i = p;
		}
	}
 
	Node* BuildHuffman() {
		Node* left, *right, *temp;
 
		while (size != 1) {
			left = Extract_min();
			right = Extract_min();
 
			temp = CreateNode(left->frequency + right->frequency);
			temp->left_child = left;
			temp->right_child = right;
			temp->frequency = left->frequency + right->frequency;
			Insert(temp);
		}
 
		return Extract_min();
	}
 
	bool Isleafnode(Node *N) {
		if (N->left_child == NULL && N->right_child == NULL)
			return true;
		return false;
	}
 
	void Encoding(Node *root, Node *code, int* input, int N) {
		Stack stack(0);
		stack.Push(root);
		Node* cur;
		int cnt = 0;
	
		while (stack.isempty() == false) {
			cur = stack.Pop();
			if (Isleafnode(cur) == true) {
				code[cnt].code = cur->code;
				code[cnt].frequency = cur->frequency;
				cnt++;
				continue;
			}
			if (cur->left_child != NULL) {
				if (cur->code == "\n")
					cur->left_child->code = "0";
				else
					cur->left_child->code = cur->code + "0";
				stack.Push(cur->left_child);
			}
			if (cur->right_child != NULL) {
				if(cur->code == "\n")
					cur->right_child->code = "1";
				else
					cur->right_child->code = cur->code + "1";
				stack.Push(cur->right_child);
			}
		}
 
	
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < N; j++) {
				if (input[i] == code[j].frequency)
					cout << code[j].code << endl;;
			}
		}
 
	}
 
};
 
int main(void) {
	int N, freq;
	int input[100];
	Node code[100];
 
	cin >> N;
 
	for (int i = 1; i <= N; i++) {
		cin >> freq;
		input[i] = freq;
	}
 
	Minheap h;
	h.InitializeMinheap(N, input);
	
	Node* f = h.BuildHuffman();
	h.Encoding(f, code, input, N);
 
 
 
 
	return 0;
}
