
#include <iostream>
#include <cstring>
#include <cstdint>
#include <python2.7/Python.h>

#define PY_MODULE_NAME	"py_test_module"

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

	dmsg("PySys_SetArgv(argc, argv)");
	PySys_SetArgv(argc, argv);

	dmsg("PyString_FromString(" PY_MODULE_NAME ")");
	PyObject * module_name = PyString_FromString(module_name_str);

	dmsg("Py_Import_Import(module_name)");
	PyObject * module = PyImport_Import(module_name);

	if(module == nullptr)
	{
		dmsg("if(module == nullptr) is True");
		PyErr_Print();
		std::cerr << "Failed to import module: " << module_name_str << " [return code = 1]" << std::endl;
		return 1;
	}

	dmsg("PyModule_GetDict(module)");
	PyObject * dict = PyModule_GetDict(module);

	if(dict == nullptr)
	{
		dmsg("if(dict == nullptr) is True");
		PyErr_Print();
		std::cerr << "Failed to get __dict__ from module: " << module_name_str << " [return code = 1]" << std::endl;
		return 1;
	}

	//
	//
	//

	std::string py_class_name = "point";
	dmsg("PyDict_GetItemString(dict, py_class_name)");
	PyObject * py_class = PyDict_GetItemString(dict, py_class_name.c_str());

	if(py_class == nullptr)
	{
		dmsg("if(py_class == nullptr) is True)");
		PyErr_Print();
		std::cerr << "Failed to import class " << py_class_name << " from module: " << module_name_str << " [return code = 1]" << std::endl;
		return 1;
	}

	PyObject * py_class_arg_tuple = PyTuple_New(2);
	PyTuple_SetItem(py_class_arg_tuple, 0, PyInt_FromLong(1337));
	PyTuple_SetItem(py_class_arg_tuple, 1, PyInt_FromLong(228));

	PyObject * obj;

	if(PyCallable_Check(py_class))
	{
		obj = PyObject_CallObject(py_class, py_class_arg_tuple);
	}
	else
	{
		std::cerr << "Failed to call class " << py_class_name << " from module: " << module_name_str << " [return code = 1]" << std::endl;
		return 1;
	}

	PyObject * value = PyObject_CallMethod(obj, "print_data", NULL);
	if(!value)
	{
		PyErr_Print();
		std::cerr << "value is NULL" << std::endl;
		return 1;
	}
	else
	{
		std::string result(PyString_AsString(value));
		std::cout << "result string = " << result << std::endl;
	}

	PyObject * value_2 = PyObject_CallMethod(obj, "func_test", NULL);
	std::cout << "value_2 is " << value_2 << std::endl;

	PyObject * value_3 = PyObject_CallMethod(obj, "func_call_rpc", NULL);
	std::cout << "value_3 is " << value_3 << std::endl;

	return 0;

}
