
#include <iostream>
#include <cstring>
#include <cstdint>
#include <python2.7/Python.h>

#define PY_MODULE_NAME	"rpyc"

void dmsg(char * msg);

void dmsg(char * msg)
{
	std::cout << "[DEBUG]:\t" << msg << std::endl;
}


int32_t main(int32_t argc, char **argv)
{

	char * module_name_str = PY_MODULE_NAME;

	dmsg("[call_func.cpp] main()");

	dmsg("Py_Initialize()");
	Py_Initialize();

	PyRun_SimpleString("import rpyc;c = rpyc.connect(\"localhost\", 18812);c.root.func_test(\"hello from PyRun_SimpleString\")");



	return 0;

}
