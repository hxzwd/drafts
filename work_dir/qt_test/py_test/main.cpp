#include <QCoreApplication>




#include "py_wrap.h"

int32_t main(int32_t argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    Py_Initialize();

//    PyRun_SimpleString("import rpyc; c = rpyc.connect(\"localhost\", 18812); c.root.func_test(\"message from qt through python\")");

//    PyRun_SimpleString("import rpyc");
//    PyRun_SimpleString("c = rpyc.connect(\"localhost\", 18812)");
//    PyRun_SimpleString("c.root.func_test(\"HELLO FROM QT\")");


    py_wrap * wrapper = new py_wrap(nullptr);

    wrapper->test_send_data(QString("wrapper->test_send_data() <- is data!!!"));
    wrapper->run_test_signal();
    wrapper->test_send_data_2(QString("test test test test test"));

    return a.exec();
}
