#include <pybind11/pybind11.h>
namespace py = pybind11;


class Enclosed {
public:
    Enclosed() { c = 4; }
    int c;
};


class TestBind {
public:
    TestBind() : _enclosed() {
        _enclosed.c = 5;
    }
    int some_height{20};
    int a_factor{0};
    bool use_stripes{false};
    Enclosed& get(int level) { _enclosed.c += level; return _enclosed; };
    int get_a() { return a_factor; }
    Enclosed _enclosed;
};


PYBIND11_MODULE(_example, m) {
    m.doc() = R"pbdoc(Buggy!)pbdoc";

    py::class_<Enclosed>(m, "Enclosed")
        .def(py::init<>())
        .def_readwrite("c", &Enclosed::c);

    py::class_<TestBind>(m, "TestBind")
        .def(py::init<>())
        .def_readwrite("some_height", &TestBind::some_height)
        .def_readwrite("a_factor", &TestBind::a_factor)
        .def_readwrite("use_stripes", &TestBind::use_stripes)
        .def_readonly("enclosed", &TestBind::_enclosed)
        .def("get", &TestBind::get)
        .def("get_a", &TestBind::get_a);

    m.attr("__version__") = "dev";
}
