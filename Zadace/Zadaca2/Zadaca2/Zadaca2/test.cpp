#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>

/*
*/

bool test_1()
{
	return true;
}

std::vector<std::function<bool()>> tests;


int main()
{
	tests.push_back(test_1);

	for (int i = 0; i < tests.size(); i++)
	{
		std::cout << "Test " << i << " " << (tests[i]()) ? "OK\n" : "BAD\n";
	}


	getchar();
	return 0;
}
