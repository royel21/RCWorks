// TestingGround.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

class MyClass
{
public:
	std::vector<int>& _vecPointer;
	MyClass(std::vector<int>& vecPointer) : _vecPointer(vecPointer)
	{
	}

	~MyClass()
	{
	}

	void printVec() {
		for (int i = 0; i < (int)_vecPointer.size(); i++) {
			std::cout << _vecPointer.data()[i] << "\n";
		}
	}
private:

};


int main()
{

	std::vector<int> vec;
	/*for (size_t i = 0; i < 20; i++)
	{
		vec.push_back(i);
	}*/

	MyClass tclass(vec);

	tclass.printVec();

	std::cin.get();
}
