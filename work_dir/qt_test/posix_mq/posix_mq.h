#ifndef POSIX_MQ_H
#define POSIX_MQ_H

#include <QObject>
#include <QtCore>

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#include "sys/types.h"
#include "unistd.h"
#include "errno.h"
#include "mqueue.h"
#include "pthread.h"

struct st_thread_misc
{
    mqd_t notified;
    void * ptr;
};

class posix_mq : public QObject
{
    Q_OBJECT
public:
    explicit posix_mq(QObject *parent = 0, int32_t msg_max_num = 10, int32_t msg_max_size = 1024);

    int32_t MESSAGE_MAX_SIZE;
    int32_t MESSAGE_MAX_NUM;
    struct mq_attr default_attr;

    QMap<QString, mqd_t> mq_info;

    QString m_src;
    QString m_trg;
    mqd_t m_notified;

    int32_t new_message_queue(char * name, int32_t oflag, int32_t mode, struct mq_attr * attr);
    int32_t new_message_queue(char * name);
    int32_t new_message_queue(QString name, int32_t oflag, int32_t mode, struct mq_attr * attr);
    int32_t new_message_queue(QString name);
    void clear_all(void);
    int32_t send_message(QString name, QString message);
    QString receive_message(QString name);
    void set_source(QString name);
    void set_target(QString name);
    int32_t write(QString message);
    QString read();
    void auto_init(void);
    void print_info(void);
//    void setup_notification(QString name, void (*thr_func)(sigval_t), mqd_t * notified);
    void setup_notification(QString name, void (*thr_func)(sigval_t), struct st_thread_misc * thr_misc);
    void debug_method(void);
    void run_notify_thread_func_signal(QString message);

signals:
//    void notify_thread_func_signal(QString message);


public slots:

//    void on_notify_thread_func_signal(QString message);

};





#endif // POSIX_MQ_H
