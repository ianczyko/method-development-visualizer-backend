cmake_minimum_required(VERSION 3.1)
project(method-development-visualizer-backend)

# Find python 3 and Boost (Boost.python)
find_package(PythonLibs 3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS python unit_test_framework)
set(CMAKE_SHARED_MODULE_PREFIX "")

# Automatically detect source files
file(GLOB_RECURSE main_SOURCES "src/*.cpp")
file(GLOB_RECURSE main_HEADERS "src/*.h")
set (main_INCLUDE_DIRS "")
foreach (_headerFile ${main_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND main_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES main_INCLUDE_DIRS)


option(ENABLE_COVERAGE "Enable coverage reporting" FALSE)
if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    link_libraries(--coverage)
endif()

add_compile_options(-Wall -std=c++14 -g)

# Add a shared module - modules are intended to be imported at runtime.
# - This is where you add the source files
add_library(method_development MODULE core_to_py_api.cpp ${main_SOURCES})

# Set up the libraries and header search paths for this target
target_link_libraries(method_development ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(method_development PRIVATE ${PYTHON_INCLUDE_DIRS} ${main_INCLUDE_DIRS})


option(TEST "Enable Boost.Test testing " FALSE)
if(TEST)
    enable_testing()
    add_executable (tester tests/test.cpp ${main_SOURCES})
    target_link_libraries(tester ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test(All_tests tester)
endif()
