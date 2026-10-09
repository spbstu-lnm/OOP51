#include "MyString.h"

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(mystring, module) {
	module.doc() = "Python bindings for MyString.";

	py::class_<MyString>(module, "MyString")
		.def(py::init<>())
		.def(py::init<const char*>(), py::arg("source"))
		.def(py::init<const std::string&>(), py::arg("source"))
		.def(py::init<const MyString&>(), py::arg("source"))
		.def(py::init<int, char>(), py::arg("count"), py::arg("character"))
		.def(py::init<const char*, int>(), py::arg("source"), py::arg("count"))
		.def(py::init<const std::string&, int>(), py::arg("source"), py::arg("count"))
		.def("clear", &MyString::clear)
		.def("shrink_to_fit", &MyString::shrink_to_fit)
		.def("c_str", [](const MyString& value) { return std::string(value.c_str()); })
		.def("size", &MyString::size)
		.def("capacity", &MyString::capacity)
		.def("empty", &MyString::empty)
		.def("insert", py::overload_cast<int, const char*>(&MyString::insert), py::arg("index"), py::arg("source"))
		.def("insert", py::overload_cast<int, const char*, int>(&MyString::insert), py::arg("index"), py::arg("source"), py::arg("count"))
		.def("insert", py::overload_cast<int, const char*, int, int>(&MyString::insert), py::arg("index"), py::arg("source"), py::arg("source_index"), py::arg("count"))
		.def("insert", py::overload_cast<int, const MyString&>(&MyString::insert), py::arg("index"), py::arg("source"))
		.def("insert", py::overload_cast<int, const MyString&, int>(&MyString::insert), py::arg("index"), py::arg("source"), py::arg("count"))
		.def("insert", py::overload_cast<int, const MyString&, int, int>(&MyString::insert), py::arg("index"), py::arg("source"), py::arg("source_index"), py::arg("count"))
		.def("insert", py::overload_cast<int, int, char>(&MyString::insert), py::arg("index"), py::arg("count"), py::arg("character"))
		.def("append", py::overload_cast<const char*>(&MyString::append), py::arg("source"))
		.def("append", py::overload_cast<const char*, int>(&MyString::append), py::arg("source"), py::arg("count"))
		.def("append", py::overload_cast<const char*, int, int>(&MyString::append), py::arg("source"), py::arg("source_index"), py::arg("count"))
		.def("append", py::overload_cast<const MyString&>(&MyString::append), py::arg("source"))
		.def("append", py::overload_cast<const MyString&, int>(&MyString::append), py::arg("source"), py::arg("count"))
		.def("append", py::overload_cast<const MyString&, int, int>(&MyString::append), py::arg("source"), py::arg("source_index"), py::arg("count"))
		.def("append", py::overload_cast<int, char>(&MyString::append), py::arg("count"), py::arg("character"))
		.def("erase", &MyString::erase, py::arg("index"), py::arg("count"))
		.def("replace", py::overload_cast<int, int, const char*>(&MyString::replace), py::arg("index"), py::arg("count"), py::arg("source"))
		.def("replace", py::overload_cast<int, int, const char*, int>(&MyString::replace), py::arg("index"), py::arg("count"), py::arg("source"), py::arg("source_count"))
		.def("replace", py::overload_cast<int, int, const char*, int, int>(&MyString::replace), py::arg("index"), py::arg("count"), py::arg("source"), py::arg("source_index"), py::arg("source_count"))
		.def("replace", py::overload_cast<int, int, const MyString&>(&MyString::replace), py::arg("index"), py::arg("count"), py::arg("source"))
		.def("replace", py::overload_cast<int, int, const MyString&, int>(&MyString::replace), py::arg("index"), py::arg("count"), py::arg("source"), py::arg("source_count"))
		.def("replace", py::overload_cast<int, int, const MyString&, int, int>(&MyString::replace), py::arg("index"), py::arg("count"), py::arg("source"), py::arg("source_index"), py::arg("source_count"))
		.def("substr", py::overload_cast<int>(&MyString::substr, py::const_), py::arg("index"))
		.def("substr", py::overload_cast<int, int>(&MyString::substr, py::const_), py::arg("index"), py::arg("count"))
		.def("compare", &MyString::compare, py::arg("other"))
		.def("find", py::overload_cast<const char*>(&MyString::find, py::const_), py::arg("source"))
		.def("find", py::overload_cast<const char*, int>(&MyString::find, py::const_), py::arg("source"), py::arg("index"))
		.def("find", py::overload_cast<const MyString&>(&MyString::find, py::const_), py::arg("source"))
		.def("find", py::overload_cast<const MyString&, int>(&MyString::find, py::const_), py::arg("source"), py::arg("index"))
		.def("__len__", &MyString::size)
		.def("__str__", [](const MyString& value) { return std::string(value.c_str()); })
		.def("__repr__", [](const MyString& value) { return "MyString('" + std::string(value.c_str()) + "')"; })
		.def("__getitem__", [](const MyString& value, int index) { return value[index]; }, py::arg("index"))
		.def("__setitem__", [](MyString& value, int index, char character) { value[index] = character; }, py::arg("index"), py::arg("character"))
		.def("__add__", py::overload_cast<const MyString&>(&MyString::operator+, py::const_), py::is_operator())
		.def("__add__", py::overload_cast<const char*>(&MyString::operator+, py::const_), py::is_operator())
		.def("__iadd__", py::overload_cast<const MyString&>(&MyString::operator+=), py::return_value_policy::reference_internal, py::is_operator())
		.def("__iadd__", py::overload_cast<const char*>(&MyString::operator+=), py::return_value_policy::reference_internal, py::is_operator())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def(py::self < py::self)
		.def(py::self <= py::self)
		.def(py::self > py::self)
		.def(py::self >= py::self);

	py::implicitly_convertible<std::string, MyString>();
}
