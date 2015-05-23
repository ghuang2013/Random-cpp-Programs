/*
  Problem Description: https://www.codeeval.com/browse/131/
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

std::pair<std::string::const_iterator, char> findOperator(const std::string& pattern)
{
	char operatorList[] = { '+', '-', '*', '\\' };
	std::string::const_iterator location;
	char currentOperator;
	for (auto oper : operatorList)
	{
		currentOperator = oper;
		location = std::find(pattern.begin(), pattern.end(), oper);
		if (location != pattern.end()) break;
	}
	return std::make_pair(location, currentOperator);
}

std::string getNumber(const std::string& testStr, const std::string& number)
{
	std::string result;
	for (const auto digit : testStr)
		result += number[digit - 'a'];
	return result;
}

int main(int argc, char *argv[])
{
	std::ifstream file("test.txt");
	std::string number, pattern;
	while (file >> number >> pattern)
	{
		std::string::const_iterator operatorLocation = findOperator(pattern).first;
		auto currentOperator = findOperator(pattern).second;
		std::string s1(pattern.begin(), operatorLocation);
		std::string s2(operatorLocation + 1, pattern.end());
		std::string number1 = getNumber(s1, number);
		std::string number2 = getNumber(s2, number);

		int result = 0;
		switch (currentOperator)
		{
		case '+':
			result = stoi(number1) + stoi(number2);
			break;
		case '-':
			result = stoi(number1) - stoi(number2);
			break;
		case '*':
			result = stoi(number1) * stoi(number2);
			break;
		case '/':
			result = stoi(number1) / stoi(number2);
		}
		std::cout << result << '\n';
	}
	return 0;
}
