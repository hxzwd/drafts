#include <QCoreApplication>

#include <c_test_class.h>
#include <c_test_class_2.h>

int32_t main(int32_t argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    c_test_class_2 obj_0;


    return a.exec();

}
