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
	Node* insert (Node* const &currentNode, const int& val) {
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
	bool search (const Node* const &currentNode, const int &val) const {
		if (currentNode == nullptr)
			return false;
		if (currentNode->value == val)
			return true;
		else if (val < currentNode->value)
			return search (currentNode->left, val);
		else
			return search (currentNode->right, val);
	}
	int sumOfBST (const Node* const &currentNode) const {
		if (currentNode == nullptr)
			return 0;
		return currentNode->value + sumOfBST (currentNode->left) + sumOfBST (currentNode->right);
	}
	template <typename Lambda>
	void travesal (const Node* const &currentNode, Lambda function) const {
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
	void pre_order (const Node* const &currentNode, Lambda function) const {
		if (currentNode == nullptr)
			return;
		pre_order (currentNode->left, function);
		pre_order (currentNode->right, function);
		function (const_cast<Node* const &>(currentNode));
	}
	int countNode (const Node* const &currentNode) const {
		if (currentNode == nullptr)
			return 0;
		return 1 + countNode (currentNode->left) + countNode (currentNode->right);
	}
	int countPositive (const Node* const &currentNode) const {
		if (currentNode == nullptr)
			return 0;
		if (currentNode->value > 0)
			return 1 + countPositive (currentNode->left) + countPositive (currentNode->right);
		else
			return countPositive (currentNode->right);
	}
	int findHeight (const Node* const &currentNode) const {
		if (currentNode == nullptr)
			return 0;
		return 1 + max (findHeight (currentNode->left), findHeight (currentNode->right));
	}
	int smallestEven (const Node* const &currentNode) const {
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
		this->pre_order (this->root, [&] (Node* const& n) {
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
	int sumOfBST () const {
		return sumOfBST (this->root);
	}
	int countNode () const {
		return countNode (this->root);
	}
	int countPositive () const {
		return countPositive (this->root);
	}
	int smallestEven () const {
		return smallestEven (this->root);
	}
	int smallestEvenWithStack () const {
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
		throw runtime_error ("\nThere is no even number");
	}
	bool search (const int& val) const {
		return search (root, val);
	}
};

int main () {
		Binary_Tree bst ({ -5, 7, -2, -6, 8, 9, -9, 0 });
		cout << "Display bst: \n" << bst;
		cout << "\nSum of bst: " << bst.sumOfBST ();
		cout << "\nCount bst: " << bst.countNode ();
		cout << "\nCount positive bst: " << bst.countPositive ();
		try {
		cout << "\nSmallest even number: " << bst.smallestEvenWithStack ();
		} catch (exception exp) {
			cout << exp.what ();
		}
		cout << '\n' << boolalpha << bst.search (-9);
		cout << '\n' << boolalpha << bst.search (-2);
		cout << '\n' << boolalpha << bst.search (-4);
		Binary_Tree bst2 ({ 3, 1, 5, 9, 5, 1 });
		cout << "\nDisplay bst2: \n" << bst2;
		cout << "\nSum of bst2: " << bst2.sumOfBST ();
		cout << "\nCount bst2: " << bst2.countNode ();
		try {
			cout << "\nSmallest even number: " << bst2.smallestEvenWithStack ();
		} catch (exception exp) {
			cout << exp.what ();
		}
		cout << '\n' << boolalpha << bst2.search (9);
		cout << '\n' << boolalpha << bst2.search (2);
		cout << '\n' << boolalpha << bst2.search (4);
		cout << endl;
	return 0;
}
