#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;


int add(int i, int j) {
    return i + j;
}

void process_array(py::array_t<double> input_array) {
    py::buffer_info buf_info = input_array.request();
    double* ptr = static_cast<double*>(buf_info.ptr);

    for (ssize_t i = 0; i < buf_info.shape[0]; i++) {
        ptr[i] = 2.0 * ptr[i]; // Example: Doubling each element
    }
}

enum class MyEnum {
    A = 0,
    B = 1,
};

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
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: scikit_build_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def(
        "add",
        &add,
        R"pbdoc(
            Add two numbers

            Some other explanation about the add function.
        )pbdoc"
    );

    m.def(
        "subtract", 
        [](int i, int j) { return i - j; }, 
        R"pbdoc(
            Subtract two numbers

            Some other explanation about the subtract function.
        )pbdoc"
    );

    m.def(
        "lol",
        [](int i) { return i + 7; },
        R"pbdoc(
            Adds 7 to the input

            Some other explanation haha.
        )pbdoc"
    );

    m.def(
        "process_array",
        &process_array,
        "Process a NumPy array"
    );

    py::enum_<MyEnum>(m, "MyEnum")
        .value("A", MyEnum::A)
        .value("B", MyEnum::B);

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

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
