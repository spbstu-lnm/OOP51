CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC

SRC_DIR = src
OUT_DIR = out

PYTHON ?= python3
PYTHON_INCLUDES := $(shell $(PYTHON) -m pybind11 --includes)
PYTHON_EXTENSION_SUFFIX := $(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))")
TARGET = $(OUT_DIR)/mystring$(PYTHON_EXTENSION_SUFFIX)

SRCS = $(SRC_DIR)/MyString.cpp $(SRC_DIR)/MyString_wrapper.cpp


.PHONY: all clean


all: $(TARGET)

$(TARGET): $(SRCS) $(SRC_DIR)/MyString.h $(SRC_DIR)/MyString_wrapper.h
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDES) -shared $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
