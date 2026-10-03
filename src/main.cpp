#include "main.h"
#include "MyString.h"

#include <iostream>


int RunDemo() {
	MyString value("MyString is ready");
	std::cout << value << '\n';
	return 0;
}


int main() { return RunDemo(); }
