cmake_minimum_required(VERSION 3.15...3.26)

# Setup the cmake environment
# dependencies required for python binding.
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)


# Python project definition.
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX
)


# Build a Python-readable cpp module.
## compile the python-readable cpp module.
set(PYTHON_MODULE_NAME _example)
python_add_library(${PYTHON_MODULE_NAME} MODULE cpp_src/example.cpp WITH_SOABI)
target_link_libraries(
    ${PYTHON_MODULE_NAME}
    PRIVATE
    pybind11::headers
)
target_compile_definitions(
    ${PYTHON_MODULE_NAME}
    PRIVATE
    VERSION_INFO=${PROJECT_VERSION}
)
## install the python-readable wrapper module
install(
    TARGETS ${PYTHON_MODULE_NAME} 
    DESTINATION ${SKBUILD_PROJECT_NAME}
)
