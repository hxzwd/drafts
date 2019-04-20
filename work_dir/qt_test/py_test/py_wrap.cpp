#include "py_wrap.h"

py_wrap::py_wrap(QObject *parent) :
    QObject(parent)
{

    qDebug() << "Initialize Python";

    Py_Initialize();

    qDebug() << "Connect to Python RPC server";

    PyRun_SimpleString("import rpyc");
    PyRun_SimpleString("c = rpyc.connect(\"localhost\", 18812)");


    connect(this, SIGNAL(test_signal(QString)), this, SLOT(on_test_signal(QString)));



}

void py_wrap::test_send_data(QString message)
{

    std::string str = message.toStdString();

    char command_buffer[2048] = { 0 };

    qDebug() << "[test_send_data()] Prepare command buffer";
    sprintf(command_buffer, "c.root.func_test(\"%s\")", str.c_str());

    qDebug() << "[test_send_data()] Run python string";
    PyRun_SimpleString(command_buffer);

}

void py_wrap::test_send_data_2(QString message)
{
    std::string str = message.toStdString();

    char command_buffer[2048] = { 0 };

    qDebug() << "[test_send_data()] Prepare command buffer";
    sprintf(command_buffer, "c.root.func_test_2(\"%s\")", str.c_str());

    qDebug() << "[test_send_data()] Run python string";

    PyObject * module_main_str = PyString_FromString("__main__");
    PyObject * module_main = PyImport_Import(module_main_str);
    sprintf(command_buffer, "def f(): return c.root.func_test_2(\"%s\")", str.c_str());

    PyRun_SimpleString(command_buffer);
    PyObject * func = PyObject_GetAttrString(module_main, "f");
    PyObject * value = PyObject_CallObject(func, NULL);



    if(!value)
    {
        qDebug() << "value is empty: value = " << value;
    }
    else
    {
        QString ret_value(PyString_AsString(value));
        qDebug() << "ret_value = " << ret_value;
    }

}

void py_wrap::run_test_signal()
{

    QString some_data("default data from run_test_signal");

    emit test_signal(some_data);
}

void py_wrap::on_test_signal(QString data)
{
    qDebug() << "In slot: on_test_signal()";
    qDebug() << "data = " << data;
    qDebug() << "call test_send_data() method()";

    test_send_data(data);

}


