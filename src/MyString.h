#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <cstddef>
#include <iosfwd>
#include <string>


class MyString {
public:
	MyString();

	MyString(const char*);
	MyString(const std::string&);
	MyString(const MyString&);

	MyString(int, char);

	MyString(const char*, int);
	MyString(const std::string&, int);
	MyString(const MyString&, int);

	~MyString();

	MyString& operator=(const MyString&);
	MyString& operator=(const char*);
	MyString& operator=(const std::string&);

	MyString& operator=(char);


	void clear();
	void shrink_to_fit();

	char* c_str();
	const char* c_str() const;

	size_t size() const;
	size_t capacity() const;
	bool empty() const;


	void insert(int, int, char);
	void insert(int, const char*);
	void insert(int, const std::string&);
	void insert(int, const MyString&);
	void insert(int, const char*, int);
	void insert(int, const std::string&, int);
	void insert(int, const MyString&, int);
	void insert(int, const char*, int, int);
	void insert(int, const std::string&, int, int);
	void insert(int, const MyString&, int, int);

	void append(int, char);
	void append(const char*);
	void append(const std::string&);
	void append(const MyString&);
	void append(const char*, int);
	void append(const std::string&, int);
	void append(const MyString&, int);
	void append(const char*, int, int);
	void append(const std::string&, int, int);
	void append(const MyString&, int, int);

	void erase(int, int);

	void replace(int, int, const char*);
	void replace(int, int, const std::string&);
	void replace(int, int, const MyString&);
	void replace(int, int, const char*, int);
	void replace(int, int, const std::string&, int);
	void replace(int, int, const MyString&, int);
	void replace(int, int, const char*, int, int);
	void replace(int, int, const std::string&, int, int);
	void replace(int, int, const MyString&, int, int);


	MyString substr(int) const;
	MyString substr(int, int) const;

	MyString operator+(const MyString&) const;
	MyString operator+(const char*) const;
	MyString operator+(const std::string&) const;

	MyString& operator+=(const MyString&);
	MyString& operator+=(const char*);
	MyString& operator+=(const std::string&);

	char& operator[](int);
	const char& operator[](int) const;

	int compare(const MyString&) const;

	bool operator==(const MyString&) const;
	bool operator!=(const MyString&) const;
	bool operator<(const MyString&) const;
	bool operator<=(const MyString&) const;
	bool operator>(const MyString&) const;
	bool operator>=(const MyString&) const;

	int find(const MyString&) const;
	int find(const char*) const;
	int find(const std::string&) const;
	int find(const MyString&, int) const;
	int find(const char*, int) const;
	int find(const std::string&, int) const;

private:
	size_t len_;
	char* buf_;
	size_t capacity_;

	void insert_data(int, const char*, int, int);
};


std::ostream& operator<<(std::ostream&, const MyString&);

#endif // _MYSTRING_H_
