CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = test
SRCS = main.cpp MyString.cpp


.PHONY: all clean


all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
