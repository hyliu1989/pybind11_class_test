#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;


class Enclosed {
public:
    Enclosed() { c = 4; }
    Enclosed(const Enclosed& other): c(other.c) {
        std::cout << "Enclosed copy constructor invoked!" << std::endl;
    } 
    int c;
};


class TestBind {
public:
    TestBind() : _enclosed() {
        _enclosed.c = 5;
    }
    Enclosed& get(int level) {
        std::cout << "TestBind::get() returns a reference." << std::endl;
        _enclosed.c += level;
        return _enclosed;
    };
    Enclosed _enclosed;
};


PYBIND11_MODULE(_example, m) {
    m.doc() = R"pbdoc(Buggy!)pbdoc";

    py::class_<Enclosed>(m, "Enclosed")
        .def(py::init<>())
        .def_readwrite("c", &Enclosed::c)
        ;

    py::class_<TestBind>(m, "TestBind")
        .def(py::init<>())
        .def_readonly("enclosed", &TestBind::_enclosed)
        .def("get", &TestBind::get)
        ;

    m.attr("__version__") = "dev";
}
