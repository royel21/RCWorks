// TestingGround.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

int main()
{

	std::vector<int*> vec;
	for (size_t i = 0; i < 20; i++)
	{
		vec.push_back(new int(i));
	}

	for (int i = (int)vec.size()-1; i > -1; i--) {
		if (i == 8) {
			delete vec[i];
			vec.erase(vec.begin() + i);
		}
		std::cout << *vec[i] << std::endl;
	}
	std::cout << vec.size() << std::endl;

	std::cin.get();
}
