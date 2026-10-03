#include "MyString.h"
#include <cstring>
#include <memory>


MyString::MyString() {
	len_ = 0;
	capacity_ = 0;

	buf_ = nullptr;
}


MyString::MyString(const char* str, size_t count) {
	capacity_ = count + 1;
	len_ = count;

	std::string_view sv(str);

	buf_ = new char[capacity_];

	size_t copied = sv.copy(buf_, len_);

	buf_[copied] = '\0';
}

MyString::MyString(std::string str, size_t count)
	: MyString(str.c_str(), count) {}

MyString::MyString(MyString& str, size_t count) 
	: MyString(str.c_str(), count) {}


char* MyString::c_str() {
	return buf_;
}


size_t MyString::size() {
	return len_;
}


size_t MyString::capacity() {
	return capacity_;
}


MyString::MyString(const char* str)
	: MyString(str, std::strlen(str)) {}

MyString::MyString(std::string str)
	: MyString(str, str.length()) {}

MyString::MyString(MyString& str)
	: MyString(str, str.size()) {}


void MyString::erase(int index, int count) {
	std::move(buf_ + index + count, buf_ + len_ + 1, buf_ + index);
}


void MyString::insert(int index, const char* str, int s_index, int count) {
	size_t new_len = len_ + count;

	if (new_len + 1 > capacity_) {
		capacity_ = new_len + 1;
		
		auto buffer = std::make_unique<char[]>(capacity_);

		std::memcpy(buffer.get(), buf_, index);
		std::memcpy(buffer.get() + index, str + s_index, count);
		std::memcpy(buffer.get() + index + count, buf_ + index, len_ - index);

		buf_ = buffer.get();
	} else {
		std::memcpy(buf_ + index + count, buf_ + index, count);
		std::memcpy(buf_ + index, str + s_index, count);
	}


	buf_[new_len] = '\0';

	len_ = new_len;
}

void MyString::insert(int index, std::string str, int s_index, int count) {
	MyString::insert(index, str.c_str(), s_index, count);
}

void MyString::insert(int index, MyString& str, int s_index, int count) {
	MyString::insert(index, str.c_str(), s_index, count);
}


void MyString::insert(int index, const char* str) {
	MyString::insert(index, str, 0, std::strlen(str));
}

void MyString::insert(int index, std::string str) {

}

void MyString::insert(int index, MyString& str) {

}


void MyString::insert(int index, const char* str, int count) {

}

void MyString::insert(int index, std::string str, int count) {

}

void MyString::insert(int index, MyString& str, int count) {

}


void MyString::insert(int index, int count, char ch) {

}
