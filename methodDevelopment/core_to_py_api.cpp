//Author: Anczykowski Igor
#include <boost/python.hpp>
#include <string>

char const* hello_cpp()
{
  return "hello from c++";
}

BOOST_PYTHON_MODULE(method_development)
{
  using namespace boost::python;
  def("hello_cpp", hello_cpp);
}