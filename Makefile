CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC_DIR = src
OUT_DIR = out

TARGET = $(OUT_DIR)/test

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/MyString.cpp


#PYTHON_CFLAGS := $(shell python3-config --cflags)
#PYTHON_LIBS   := $(shell python3-config --libs --embed)

#CXXFLAGS += $(PYTHON_CFLAGS)
#LDFLAGS  += $(PYTHON_LIBS)


.PHONY: all clean


all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
