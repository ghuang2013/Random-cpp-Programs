#include <iostream>
#include <vector>
#include <deque>

using namespace std;
//non-generic version:
template<typename T>
void insertionSort(vector<T>& arr){
	for (unsigned int i = 1; i < arr.size(); ++i)
	{
		T tmp = arr[i];
		for (i; i > 0 && tmp < arr[i - 1]; --i){
			arr[i] = arr[i - 1];
		}
		arr[i] = tmp;
	}
}

//generic version:
template<typename Iterator>
void insertionSort(Iterator begin, Iterator end){
	insertionSort(begin, end, less<Iterator::value_type>());
}

template <typename Iterator, typename Compare>
void insertionSort(Iterator begin, Iterator end, Compare less)
{
	for (Iterator insertItem = begin + 1; insertItem != end; ++insertItem)
	{
		Iterator::value_type tmp = *insertItem;
		while (insertItem != begin && less(tmp, *(insertItem - 1)))
		{
			*insertItem = *(insertItem - 1);
			--insertItem;
		}
		*insertItem = tmp;
	}
}

int main()
{
	vector<int> arr = { 5, 4, 10, 1, 2, 7, 3, 9 };
	//insertionSort(arr);
	insertionSort(arr.begin(), arr.end());
	for (const auto& i : arr)
		cout << i << ' ';
	cout << endl;
	deque<int> arr2 = { 5, 4, 10, 1, 2, 7, 3, 9 };
	//insertionSort(arr);
	insertionSort(arr2.begin(), arr2.end());
	for (const auto& i : arr2)
		cout << i << ' ';
	return 0;
}
