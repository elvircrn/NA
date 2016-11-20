#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>

#include "main.cpp"

/*
*/

bool test_1()
{
}

std::vector<std::function<bool()>> tests;


int main()
{
    tests.push_back(test_1);

    for (int i = 0; i < tests.size(); i++)
    {
        std::cout << "Test " << i << " " << (test [i]()) ? "OK\n" : "BAD\n";
    }


    return 0;
}
