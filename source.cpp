#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <limits>
#include <stack>
#include <stdexcept>

using namespace std;

class Binary_Tree {
private:
	Binary_Tree (const Binary_Tree& bst); //no copy ctor
	Binary_Tree& operator = (const Binary_Tree&); //no assignment operator
	class Node {
		friend class Binary_Tree; //allow access
	public:
		Node (int val, Node* left = nullptr, Node* right = nullptr) : value (val), left (left), right (right) {/*empty body*/
		}
	private:
		Node* left;
		Node* right;
		int value;
	}*root;
	Node* insert (Node* currentNode, const int& val) {
		if (currentNode == nullptr)
			return new Node (val);
		if (val <= currentNode->value) {
			currentNode->left = insert (currentNode->left, val);
			//return currentNode;
		}
		else if (val >= currentNode->value) {
			currentNode->right = insert (currentNode->right, val);
			//return currentNode;
		}
		//currentNode keeps track of the current state
		return currentNode;
	}
	int sumOfBST (Node* currentNode) {
		if (currentNode == nullptr)
			return 0;
		return currentNode->value + sumOfBST (currentNode->left) + sumOfBST (currentNode->right);
	}
	template <typename Lambda>
	void travesal (Node* currentNode, Lambda function) const {
		if (currentNode == nullptr)
			return;
		travesal (currentNode->left, function);
		function (currentNode->value);
		travesal (currentNode->right, function);
	}
	template <typename Lambda>
	void traversalWithStack (Lambda function) const {
		stack<Node*> s;
		Node* n = root;
		while (n != nullptr || !s.empty ()) { //if either condition met, go to the loop
			for (; n != nullptr; n = n->left) {
				s.push (n);
			}
			if (!s.empty ()) {
				function (s.top ()->value);
				n = s.top ()->right;
				s.pop ();
			}
		}
	}
	template <typename Lambda>
	void pre_order (Node* currentNode, Lambda function) const {
		if (currentNode == nullptr)
			return;
		pre_order (currentNode->left, function);
		pre_order (currentNode->right, function);
		function (currentNode);
	}
	int countNode (Node* currentNode) {
		if (currentNode == nullptr)
			return 0;
		return 1 + countNode (currentNode->left) + countNode (currentNode->right);
	}
	int countPositive (Node* currentNode) {
		if (currentNode == nullptr)
			return 0;
		if (currentNode->value > 0)
			return 1 + countPositive (currentNode->left) + countPositive (currentNode->right);
		else
			return countPositive (currentNode->right);
	}
	int findHeight (Node* currentNode) {
		if (currentNode == nullptr)
			return 0;
		return 1 + max (findHeight (currentNode->left), findHeight (currentNode->right));
	}
	int smallestEven (Node* currentNode) {
		int smallest = std::numeric_limits<int>::max ();
		travesal (currentNode, [&] (const int& val) {
			if (val % 2 == 0 && val < smallest) smallest = val;
		});
		return smallest;
	}
public:
	Binary_Tree (const initializer_list<int>& list) {
		for (const auto& num : list)
			this->root = insert (root, num);
	}
	~Binary_Tree () {
		this->pre_order (this->root, [&] (Node* & n) {
			delete n;
		});
	}
	/*
	Use in-order for display, use pre-order for de-allocation
	*/
	friend ostream& operator<<(ostream& out, const Binary_Tree& bst) {
		bst.traversalWithStack ([&] (const int& val) {
			out << val << ' ';	});
		return out;
	}
	int sumOfBST () {
		return sumOfBST (this->root);
	}
	int countNode () {
		return countNode (this->root);
	}
	int countPositive () {
		return countPositive (this->root);
	}
	int smallestEven () {
		return smallestEven (this->root);
	}
	int smallestEvenWithStack () {
		stack<Node*>s;
		Node* n = root;
		while (n != nullptr || !s.empty ()) {
			for (; n != nullptr; n = n->left) {
				if (n->value % 2 == 0) {
					return n->value;
				}
				s.push (n);
			}
			if (!s.empty ()) {
				n = s.top ()->right;
				s.pop ();
			}
		}
		throw runtime_error ("\nThere is no even number\n");
	}
};

int main () {
	try {
		Binary_Tree bst ({ -5, 7, -2, -6, 8, 9, -9, 0 });
		cout << "Display bst: \n" << bst;
		cout << "\nSum of bst: " << bst.sumOfBST ();
		cout << "\nCount bst: " << bst.countNode ();
		cout << "\nCount positive bst: " << bst.countPositive ();
		cout << "\nSmallest even number: " << bst.smallestEvenWithStack ();
		Binary_Tree bst2 ({ 3, 1, 5, 9, 5, 1 });
		cout << "\nDisplay bst2: \n" << bst2;
		cout << "\nSum of bst2: " << bst2.sumOfBST ();
		cout << "\nCount bst2: " << bst2.countNode ();
		cout << "\nSmallest even number: " << bst2.smallestEvenWithStack ();
		cout << endl;
	} catch (exception exp) {
		cout << exp.what ();
	}
	return 0;
}
