#include "MyString.h"

#include <cstring>
#include <ostream>
#include <memory>
#include <stdexcept>


namespace {
const char cEmptyString[] = "";


void CheckSource(const char* source) {
	if (source == nullptr) {
		throw std::invalid_argument("MyString source must not be null");
	}
}


void CheckRange(int index, int count, size_t length) {
	if (index < 0 || count < 0 || static_cast<size_t>(index) > length ||
		static_cast<size_t>(count) > length - static_cast<size_t>(index)) {

		throw std::out_of_range("MyString index or count is out of range");
	}
}


size_t SourceLength(const char* source) {
	CheckSource(source);

	return std::strlen(source);
}
}


MyString::MyString() : len_(0), buf_(nullptr), capacity_(0) {}


MyString::MyString(const char* source) 
	: MyString(source, static_cast<int>(SourceLength(source))) {}


MyString::MyString(const std::string& source) 
	: MyString(source.c_str(), static_cast<int>(source.size())) {}


MyString::MyString(const MyString& source) 
	: MyString(source.c_str(), static_cast<int>(source.size())) {}


MyString::MyString(int count, char character) : MyString() {
	if (count < 0) {
		throw std::out_of_range("MyString count must not be negative");
	}

	if (count > 0) {
		capacity_ = static_cast<size_t>(count) + 1;

		buf_ = new char[capacity_];

		for (int i = 0; i < count; ++i) {
			buf_[i] = character;
		}
		buf_[len_] = '\0';

		len_ = static_cast<size_t>(count);
	}
}


MyString::MyString(const char* source, int count) : MyString() {
	CheckSource(source);

	if (count < 0 || static_cast<size_t>(count) > std::strlen(source)) {
		throw std::out_of_range("MyString count exceeds source length");
	}

	if (count > 0) {
		len_ = static_cast<size_t>(count);
		capacity_ = len_ + 1;

		buf_ = new char[capacity_];

		std::memcpy(buf_, source, len_);
		buf_[len_] = '\0';
	}
}


MyString::MyString(const std::string& source, int count) 
	: MyString(source.c_str(), count) {}


MyString::MyString(const MyString& source, int count) 
	: MyString(source.c_str(), count) {}


MyString::~MyString() { delete[] buf_; }


MyString& MyString::operator=(const MyString& source) {
	if (this != &source) {
		MyString copy(source);

		*this = copy.c_str();
	}

	return *this;
}


MyString& MyString::operator=(const char* source) {
	CheckSource(source);

	const size_t source_length = std::strlen(source);

	std::unique_ptr<char[]> copy(new char[source_length + 1]);
	std::memcpy(copy.get(), source, source_length + 1);

	if (source_length + 1 > capacity_) {
		delete[] buf_;

		capacity_ = source_length + 1;
		buf_ = copy.release();
	} else if (buf_ != nullptr) {
		std::memcpy(buf_, copy.get(), source_length + 1);
	}

	len_ = source_length;

	return *this;
}


MyString& MyString::operator=(const std::string& source) {
	return *this = source.c_str();
}


MyString& MyString::operator=(char character) {
	if (capacity_ < 2) {
		std::unique_ptr<char[]> buffer(new char[2]);

		buffer[0] = character;
		buffer[1] = '\0';

		delete[] buf_;

		buf_ = buffer.release();

		capacity_ = 2;
	} else {
		buf_[0] = character;
		buf_[1] = '\0';
	}
	len_ = 1;

	return *this;
}

void MyString::clear() {
	len_ = 0;

	if (buf_ != nullptr) {
		buf_[0] = '\0';
	}
}


void MyString::shrink_to_fit() {
	if (capacity_ == len_ + 1) return;

	if (len_ == 0) {
		delete[] buf_;

		buf_ = nullptr;
		capacity_ = 0;

		return;
	}

	std::unique_ptr<char[]> buffer(new char[len_ + 1]);
	std::memcpy(buffer.get(), buf_, len_ + 1);

	delete[] buf_;
	buf_ = buffer.release();

	capacity_ = len_ + 1;
}


char* MyString::c_str() {
	return buf_ == nullptr ? const_cast<char*>(cEmptyString) : buf_; 
}


const char* MyString::c_str() const {
	return buf_ == nullptr ? cEmptyString : buf_;
}


size_t MyString::size() const { return len_; }


size_t MyString::capacity() const { return capacity_; }


bool MyString::empty() const { return len_ == 0; }


void MyString::insert_data(int index, const char* source, int source_index, int count) {
	CheckSource(source);
	CheckRange(index, 0, len_);

	if (source_index < 0 || count < 0 || static_cast<size_t>(source_index) > std::strlen(source) ||
		static_cast<size_t>(count) > std::strlen(source) - static_cast<size_t>(source_index)) {

		throw std::out_of_range("MyString source range is out of range");
	}

	if (count == 0) return;

	const size_t added = static_cast<size_t>(count);
	const size_t new_length = len_ + added;

	std::unique_ptr<char[]> source_copy(new char[added]);
	std::memcpy(source_copy.get(), source + source_index, added);

	const size_t new_capacity = 
		new_length + 1 > capacity_ ? new_length + 1 : capacity_;

	std::unique_ptr<char[]> buffer(new char[new_capacity]);

	if (index > 0) {
		std::memcpy(buffer.get(), c_str(), static_cast<size_t>(index));
	}

	std::memcpy(buffer.get() + index, source_copy.get(), added);

	if (len_ > static_cast<size_t>(index)) {
		std::memcpy(
			buffer.get() + index + added, 
			c_str() + index, 
			len_ - static_cast<size_t>(index)
		);
	}

	buffer[new_length] = '\0';

	delete[] buf_;
	buf_ = buffer.release();

	len_ = new_length;
	capacity_ = new_capacity;
}


void MyString::insert(int index, int count, char character) {
	CheckRange(index, 0, len_);

	if (count < 0) throw std::out_of_range("MyString count must not be negative");
	if (count == 0) return;

	const size_t added = static_cast<size_t>(count);
	const size_t new_length = len_ + added;
	const size_t new_capacity = 
		new_length + 1 > capacity_ ? new_length + 1 : capacity_;

	std::unique_ptr<char[]> buffer(new char[new_capacity]);

	if (index > 0) {
		std::memcpy(
			buffer.get(), 
			c_str(), 
			static_cast<size_t>(index)
		);
	}

	for (size_t i = 0; i < added; ++i) {
		buffer[static_cast<size_t>(index) + i] = character;
	}

	if (len_ > static_cast<size_t>(index)) {
		std::memcpy(
			buffer.get() + index + added, 
			c_str() + index, 
			len_ - static_cast<size_t>(index)
		);
	}

	buffer[new_length] = '\0';

	delete[] buf_;

	buf_ = buffer.release();
	len_ = new_length;
	capacity_ = new_capacity;
}


void MyString::insert(int i, const char* s) { 
	insert_data(i, s, 0, static_cast<int>(SourceLength(s))); 
}


void MyString::insert(int i, const std::string& s) { 
	insert(i, s.c_str()); 
}


void MyString::insert(int i, const MyString& s) { 
	insert(i, s.c_str()); 
}


void MyString::insert(int i, const char* s, int n) { 
	insert_data(i, s, 0, n); 
}


void MyString::insert(int i, const std::string& s, int n) { 
	insert(i, s.c_str(), n); 
}


void MyString::insert(int i, const MyString& s, int n) { 
	insert(i, s.c_str(), n); 
}


void MyString::insert(int i, const char* s, int si, int n) { 
	insert_data(i, s, si, n); 
}


void MyString::insert(int i, const std::string& s, int si, int n) { 
	insert(i, s.c_str(), si, n); 
}


void MyString::insert(int i, const MyString& s, int si, int n) { 
	insert(i, s.c_str(), si, n); 
}


void MyString::append(int count, char character) { 
	insert(static_cast<int>(len_), count, character); 
}


void MyString::append(const char* source) { 
	insert(static_cast<int>(len_), source); 
}


void MyString::append(const std::string& source) { 
	append(source.c_str()); 
}


void MyString::append(const MyString& source) { 
	append(source.c_str()); 
}


void MyString::append(const char* source, int count) { 
	insert(static_cast<int>(len_), source, count); 
}


void MyString::append(const std::string& source, int count) { 
	append(source.c_str(), count); 
}


void MyString::append(const MyString& source, int count) { 
	append(source.c_str(), count); 
}


void MyString::append(const char* source, int si, int count) { 
	insert(static_cast<int>(len_), source, si, count); 
}


void MyString::append(const std::string& source, int si, int count) { 
	append(source.c_str(), si, count); 
}


void MyString::append(const MyString& source, int si, int count) { 
	append(source.c_str(), si, count); 
}


void MyString::erase(int index, int count) {
	CheckRange(index, count, len_);

	const size_t remaining = len_ - static_cast<size_t>(count);

	if (count > 0) {
		std::memmove(
			buf_ + index, 
			buf_ + index + count, 
			remaining - static_cast<size_t>(index) + 1
		);

		len_ = remaining;
	}
}


void MyString::replace(int i, int n, const char* s) { 
	replace(i, n, s, 0, static_cast<int>(SourceLength(s))); 
}


void MyString::replace(int i, int n, const std::string& s) { 
	replace(i, n, s.c_str()); 
}


void MyString::replace(int i, int n, const MyString& s) { 
	replace(i, n, s.c_str()); 
}


void MyString::replace(int i, int n, const char* s, int sn) { 
	replace(i, n, s, 0, sn); 
}


void MyString::replace(int i, int n, const std::string& s, int sn) { 
	replace(i, n, s.c_str(), sn); 
}


void MyString::replace(int i, int n, const MyString& s, int sn) { 
	replace(i, n, s.c_str(), sn); 
}


void MyString::replace(int index, int count, const char* source, int source_index, int source_count) {
	CheckRange(index, count, len_);

	MyString tail = substr(index + count);
	MyString prefix = substr(0, index);

	prefix.insert(static_cast<int>(prefix.size()), source, source_index, source_count);
	prefix.append(tail);

	*this = prefix;
}


void MyString::replace(int i, int n, const std::string& s, int si, int sn) { 
	replace(i, n, s.c_str(), si, sn); 
}


void MyString::replace(int i, int n, const MyString& s, int si, int sn) { 
	replace(i, n, s.c_str(), si, sn); 
}


MyString MyString::substr(int index) const {
	CheckRange(index, 0, len_);

	return substr(index, static_cast<int>(len_ - static_cast<size_t>(index)));
}


MyString MyString::substr(int index, int count) const {
	CheckRange(index, count, len_);

	return MyString(c_str() + index, count);
}


MyString MyString::operator+(const MyString& source) const { 
	MyString result(*this); 
	
	result.append(source); 
	
	return result; 
}


MyString MyString::operator+(const char* source) const { 
	MyString result(*this); 
	
	result.append(source); 
	
	return result; 
}


MyString MyString::operator+(const std::string& source) const { 
	return *this + source.c_str(); 
}


MyString& MyString::operator+=(const MyString& source) { 
	append(source); 
	
	return *this; 
}


MyString& MyString::operator+=(const char* source) { 
	append(source); 
	
	return *this; 
}


MyString& MyString::operator+=(const std::string& source) { 
	append(source); 

	return *this; 
}


char& MyString::operator[](int index) { 
	CheckRange(index, 0, len_); 

	if (static_cast<size_t>(index) == len_) {
		throw std::out_of_range("MyString index is out of range"); 
	}

	return buf_[index]; 
}


const char& MyString::operator[](int index) const { 
	CheckRange(index, 0, len_); 

	if (static_cast<size_t>(index) == len_) {
		throw std::out_of_range("MyString index is out of range"); 
	}

	return buf_[index]; 
}


int MyString::compare(const MyString& other) const {
	const size_t common = len_ < other.len_ ? len_ : other.len_;

	for (size_t i = 0; i < common; ++i) {
		if (buf_[i] < other.buf_[i]) return -1;
		if (buf_[i] > other.buf_[i]) return 1;
	}

	if (len_ < other.len_) return -1;
	if (len_ > other.len_) return 1;

	return 0;
}


bool MyString::operator==(const MyString& other) const { 
	return compare(other) == 0; 
}


bool MyString::operator!=(const MyString& other) const { 
	return compare(other) != 0; 
}


bool MyString::operator<(const MyString& other) const { 
	return compare(other) < 0; 
}


bool MyString::operator<=(const MyString& other) const { 
	return compare(other) <= 0; 
}


bool MyString::operator>(const MyString& other) const { 
	return compare(other) > 0; 
}


bool MyString::operator>=(const MyString& other) const { 
	return compare(other) >= 0; 
}


int MyString::find(const MyString& source) const { 
	return find(source.c_str(), 0); 
}


int MyString::find(const char* source) const { 
	return find(source, 0); 
}


int MyString::find(const std::string& source) const { 
	return find(source.c_str(), 0); 
}


int MyString::find(const MyString& source, int index) const { 
	return find(source.c_str(), index); 
}


int MyString::find(const std::string& source, int index) const { 
	return find(source.c_str(), index); 
}


int MyString::find(const char* source, int index) const {
	CheckSource(source);

	if (index < 0 || static_cast<size_t>(index) > len_) {
		throw std::out_of_range("MyString search index is out of range");
	}

	const size_t source_length = std::strlen(source);

	if (source_length == 0) return index;
	if (source_length > len_ - static_cast<size_t>(index)) return -1;

	for (size_t i = static_cast<size_t>(index); i <= len_ - source_length; ++i) {
		size_t j = 0;

		while (j < source_length && buf_[i + j] == source[j]) ++j;

		if (j == source_length) return static_cast<int>(i);
	}

	return -1;
}


std::ostream& operator<<(std::ostream& output, const MyString& value) {
	return output << value.c_str();
}
