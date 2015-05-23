#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iterator>   

using namespace std;

namespace MergeSort{
	template <typename T>
	using remRef = typename remove_reference<T>::type;

	template <typename T>
	remRef<T&>&& move(T && arg)
	{
		return static_cast<remRef<T&>&&>(arg);
	}

	template <typename Iter, typename Cont>
	void move(Iter begin, Iter end, Cont &container){
		while (begin != end){
			container.push_back(move(*begin));
			++begin;
		}
	}
}

template<typename T>
void mergeSort(vector<T> &v){
	mergeSort(v, 0, v.size() - 1);
}

template<typename T>
void mergeSort(vector<T>& v, size_t startIdx, size_t endIdx){
	if (startIdx != endIdx){
		size_t midpoint = (startIdx + endIdx) / 2;
		mergeSort(v, startIdx, midpoint);
		mergeSort(v, midpoint + 1, endIdx);
		merge(v, startIdx, midpoint + 1, endIdx);
	}
}

template<typename T>
void merge(vector<T> &v, size_t left, size_t right, size_t last)
{
	vector<T> v1, v2;
	auto begin = v.begin(), end = v.begin() + last;
	//move(begin + left, begin + right, back_inserter(v1));
	//move(begin + right, end + 1, back_inserter(v2));
	MergeSort::move(begin + left, begin + right,v1);
	MergeSort::move(begin + right, end + 1, v2);
	v1.push_back(numeric_limits<T>::max());
	v2.push_back(numeric_limits<T>::max());
	size_t i1 = 0, i2 = 0;
	while (left <= last){
		v.at(left++) = (v1.at(i1) < v2.at(i2)) ? v1.at(i1++) : v2.at(i2++);
	}
}

int main()
{
	vector<int> v = { 7, 3, 1, 7, 4, 8, 12, 2, 9, 4, 10 };
	mergeSort(v);
	for (const auto& num : v) 
		cout << num << ' ';
	return 0;
}
