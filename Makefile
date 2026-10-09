CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC

SRC_DIR = src
OUT_DIR = out

PYTHON = .venv/bin/python3
PYTHON_INCLUDES := $(shell $(PYTHON) -m pybind11 --includes)
PYTHON_EXTENSION_SUFFIX := $(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))")
TARGET = $(OUT_DIR)/mystring$(PYTHON_EXTENSION_SUFFIX)

SRCS = $(SRC_DIR)/MyString.cpp $(SRC_DIR)/MyString_wrapper.cpp


.PHONY: all clean graph


all: $(TARGET)

$(TARGET): $(SRCS) $(SRC_DIR)/MyString.h
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDES) -shared $(SRCS) -o $(TARGET)

graph: $(SRCS) $(SRC_DIR)/MyString.h
	@mkdir -p $(OUT_DIR) && cd $(OUT_DIR) && \
	$(CXX) $(CXXFLAGS) -O1 -g0 -emit-llvm -S $(PYTHON_INCLUDES) ../$(SRC_DIR)/MyString.cpp ../$(SRC_DIR)/MyString_wrapper.cpp && \
	llvm-link MyString.ll MyString_wrapper.ll -o merged.ll && \
	opt -passes=dot-callgraph -disable-output merged.ll && \
	llvm-cxxfilt < merged.ll.callgraph.dot > clean_callgraph.dot && \
	sed -E '/label=/ { s/</\\</g; s/>/\\>/g }' clean_callgraph.dot > safe_callgraph.dot

clean:
	rm -rf $(OUT_DIR)

