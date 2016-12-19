#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>


std::vector<std::function<bool()>> tests;


int main()
{

	for (int i = 0; i < tests.size(); i++)
	{
		std::cout << "Test " << i << " " << (tests[i]()) ? "OK\n" : "BAD\n";
	}


	getchar();
	return 0;
}
