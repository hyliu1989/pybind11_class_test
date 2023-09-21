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

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
