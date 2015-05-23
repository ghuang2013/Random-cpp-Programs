#include <iostream>
#include <vector> 
#include <initializer_list>
#include <algorithm>

using namespace std;

class Heap {
public:
	Heap (const initializer_list<int> &list) :vElements{} {
		for (const auto& val : list)
			insertion (val);
	}
	void insertion (const int& val) {
		vElements.push_back (val);
		cout << "You have just inserted value: " << val << " onto the heap\n";
		heapifyUp (vElements.size () - 1);
	}
	void removal (const int& key) {
		auto location = find (vElements.begin (), vElements.end (), key);
		if (location == vElements.end ())
			return;
		size_t keyIdx = location - vElements.begin ();
		swap (vElements[keyIdx], vElements[vElements.size () - 1]);
		vElements.pop_back ();
		heapifyDown (keyIdx);
	}
	size_t getParentIndex (const size_t& childIdx) const {
		if (childIdx % 2 == 0) {
			return childIdx / 2 - 1;
		}
		else {
			return childIdx / 2;
		}
	}
	pair<size_t, size_t> getChildren (const size_t& parentIdx) const {
		size_t leftChild = parentIdx * 2 + 1;
		size_t rightChild = parentIdx * 2 + 2;
		return make_pair (leftChild, rightChild);
	}
	void print () const {
		for (const auto& val : vElements)
			cout << val << endl;
	}
	void sort () {
		vector<int> newVector;
		while (!vElements.empty ()) {
			cout << vElements[0] << ' ';
			newVector.push_back (vElements[0]);
			removal (vElements[0]);
		}
		vElements = newVector;
	}
private:
	void heapifyUp (size_t index) {
		while (index > 0) {
			size_t parentIdx = getParentIndex (index);
			if (vElements[index] > vElements[parentIdx]) { //exchange
				swap (vElements[index], vElements[parentIdx]);
			}
			else return;
			index = parentIdx;
		}
	}
	void heapifyDown (size_t index) {
		while (!vElements.empty () && index * 2 + 1 <= vElements.size () - 1) {
			int maxChildIdx;
			size_t leftIdx = getChildren (index).first;
			size_t rightIdx = getChildren (index).second;
			if (rightIdx > vElements.size () - 1)
				maxChildIdx = leftIdx;
			else {
				(vElements[leftIdx] > vElements[rightIdx]) ?
					maxChildIdx = leftIdx : maxChildIdx = rightIdx;
			}
			if (vElements[maxChildIdx] > vElements[index]) {
				swap (vElements[maxChildIdx], vElements[index]);
			}
			else return;
			index = maxChildIdx;
		}
	}
	vector<int> vElements;
};

int main () {
	Heap heap ({ 1, 3, 6, 5, 9, 8, -2 });
	cout << "Before removal: \n";
	heap.print ();
	cout << "\nAfter sort: \n";
	heap.sort ();
	heap.print ();
	return 0;
}
