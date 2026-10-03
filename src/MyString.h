#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <cstddef>
#include <iosfwd>
#include <string>

class MyString {
public:
	MyString();

	MyString(const char* source);
	MyString(const std::string& source);
	MyString(const MyString& source);

	MyString(int count, char character);

	MyString(const char* source, int count);
	MyString(const std::string& source, int count);
	MyString(const MyString& source, int count);

	~MyString();


	MyString& operator=(const MyString& source);
	MyString& operator=(const char* source);
	MyString& operator=(const std::string& source);

	MyString& operator=(char character);


	void clear();
	void shrink_to_fit();

	char* c_str();
	const char* c_str() const;

	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	void insert(int index, int count, char character);
	void insert(int index, const char* source);
	void insert(int index, const std::string& source);
	void insert(int index, const MyString& source);
	void insert(int index, const char* source, int count);
	void insert(int index, const std::string& source, int count);
	void insert(int index, const MyString& source, int count);
	void insert(int index, const char* source, int source_index, int count);
	void insert(int index, const std::string& source, int source_index, int count);
	void insert(int index, const MyString& source, int source_index, int count);

	void append(int count, char character);
	void append(const char* source);
	void append(const std::string& source);
	void append(const MyString& source);
	void append(const char* source, int count);
	void append(const std::string& source, int count);
	void append(const MyString& source, int count);
	void append(const char* source, int source_index, int count);
	void append(const std::string& source, int source_index, int count);
	void append(const MyString& source, int source_index, int count);

	void erase(int index, int count);

	void replace(int index, int count, const char* source);
	void replace(int index, int count, const std::string& source);
	void replace(int index, int count, const MyString& source);
	void replace(int index, int count, const char* source, int source_count);
	void replace(int index, int count, const std::string& source, int source_count);
	void replace(int index, int count, const MyString& source, int source_count);
	void replace(int index, int count, const char* source, int source_index, int source_count);
	void replace(int index, int count, const std::string& source, int source_index, int source_count);
	void replace(int index, int count, const MyString& source, int source_index, int source_count);

	MyString substr(int index) const;
	MyString substr(int index, int count) const;

	MyString operator+(const MyString& source) const;
	MyString operator+(const char* source) const;
	MyString operator+(const std::string& source) const;

	MyString& operator+=(const MyString& source);
	MyString& operator+=(const char* source);
	MyString& operator+=(const std::string& source);

	char& operator[](int index);
	const char& operator[](int index) const;

	int compare(const MyString& other) const;

	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator>=(const MyString& other) const;

	int find(const MyString& source) const;
	int find(const char* source) const;
	int find(const std::string& source) const;
	int find(const MyString& source, int index) const;
	int find(const char* source, int index) const;
	int find(const std::string& source, int index) const;

private:
	size_t len_;
	char* buf_;
	size_t capacity_;

	void insert_data(int index, const char* source, int source_index, int count);
};

std::ostream& operator<<(std::ostream& output, const MyString& value);

#endif // _MYSTRING_H_
