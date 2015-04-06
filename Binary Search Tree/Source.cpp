#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include "BST.h"

int main()
{
	std::cout << "BST OF INT:\n";
	BST<int> Tree;
	std::random_device generator;
	std::uniform_int_distribution<int> intRnd(1, 100);
	for (int i = 0; i < 30; ++i)
	{
		Tree.addElement(intRnd(generator));
	}
	std::cout << Tree;
	int num;
	std::cout << "Enter numbers that you want to remove: \n";
	while (std::cin >> num)
	{
		Tree.removeElement(num);
		std::cout << "Display:\n";
		std::cout << Tree;
	}
	std::cin.clear();

	std::cout << "BST OF STRING:\n";
	BST<std::string> sTree;
	std::uniform_int_distribution<int> charRnd(97, 122);
	std::uniform_int_distribution<int> sizeRnd(4, 8);
	for (int i = 0; i < 5; ++i)
	{
		std::string result(sizeRnd(generator), '?');
		std::for_each(result.begin(), result.end(), [&charRnd, &generator](char &rndChar)
		{rndChar = static_cast<char>(charRnd(generator)); });
		sTree.addElement(result);
	}
	std::cout << sTree;
	std::string s;
	std::cout << "Enter strings that you want to remove: \n";
	while (std::cin >> s)
	{
		sTree.removeElement(s);
		std::cout << "Display:\n";
		std::cout << sTree;
	}
	return 0;
}