#ifndef PY_WRAP_H
#define PY_WRAP_H

#include <QObject>
#include <QtCore>

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


#include "python2.7/Python.h"

class py_wrap : public QObject
{
    Q_OBJECT
public:
    explicit py_wrap(QObject *parent = 0);
    void test_send_data(QString message);
    void test_send_data_2(QString message);
    void run_test_signal(void);

signals:
    void test_signal(QString data);

public slots:
    void on_test_signal(QString data);

};

#endif // PY_WRAP_H
