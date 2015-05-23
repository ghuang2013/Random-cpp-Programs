/*
  Reading input file content into a struct
  Example file:
  Guan Huang 12345 67890
  Someone 33655 324562
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Person{
	std::string name;
	std::vector<std::string> phoneNum;
};

void process(std::string line, std::vector<Person> & v)
{
	/*
		sstream	solution:
	*/

	Person newPerson;
	std::istringstream lnstream(line);
	std::string nameToken;
	while (!isdigit(lnstream.peek()) && getline(lnstream, nameToken, ' '))
	{  //peek only works with getline :(
		newPerson.name += nameToken + " ";
	}
	newPerson.name.pop_back();
	std::string numberToken;
	while (getline(lnstream, numberToken, ' '))
	{
		newPerson.phoneNum.push_back(numberToken);
	}
	v.push_back(newPerson);

	/*
		algorithm solution:
	*/
	//Person newPerson;
	//auto digit = std::find_if(line.begin(), line.end(),
	//	[&newPerson](char c){ return isdigit(c); });

	//newPerson.name.assign(line.begin(), digit);
	//
	//std::string num = line.substr(digit - line.begin());
	//auto fLetter = num.begin();
	//auto it = find(fLetter, num.end(), ' ');
	//while (it != num.end())
	//{
	//	newPerson.phoneNum.push_back(std::string(fLetter, it));
	//	fLetter = it + 1;
	//	it = find(fLetter, num.end(), ' ');
	//}
	//newPerson.phoneNum.push_back(std::string(fLetter, num.end()));
	//v.push_back(newPerson);
}

int main()
{
	std::ifstream file("test.txt");
	std::vector<Person> vPerson;
	std::string line;
	while (getline(file, line))
	{
		process(line, vPerson);
	}
	for (auto someone = vPerson.begin(); someone != vPerson.end(); ++someone)
	{
		std::cout << someone->name << std::endl;
		for (const auto& number : someone->phoneNum)
			std::cout << number << std::endl;
	}
	return 0;
}
