#ifndef _MY_STRING_H
#define _MY_STRING_H

#include <cstddef>
#include <string>
#include <cstring>
#include <string_view>
#include <algorithm>

class MyString {
private:
	size_t len_;
	char* buf_;
	size_t capacity_;

public:
	MyString();

	MyString(const char*);
	MyString(std::string);
	MyString(MyString&);

	MyString(const char*, size_t);
	MyString(std::string, size_t);
	MyString(MyString&, size_t);
	
	void insert(int, const char*, int, int);
	void insert(int, std::string, int, int);
	void insert(int, MyString&, int, int);
	
	void insert(int, const char*);
	void insert(int, std::string);
	void insert(int, MyString&);

	void insert(int, const char*, int);
	void insert(int, std::string, int);
	void insert(int, MyString&, int);

	void insert(int, int, char);

	void erase(int, int);
	
	char* c_str();
	
	size_t size();
	size_t capacity();
};

#endif	// ifndef _MY_STRING_H
