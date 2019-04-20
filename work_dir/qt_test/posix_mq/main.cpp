#include <QCoreApplication>

#include "posix_mq.h"

//static void func_notify(union sigval sv)
//{

//    struct sigevent sev;
//    mqd_t handle_notified;
//    char message_buffer[8192] = { 0 };
//    uint32_t message_max_size;
//    ssize_t bytes_read;

//    message_max_size = 1024;

//    qDebug() << "In func_notify()";

//    handle_notified = *((mqd_t *)(sv.sival_ptr));

//    qDebug() << "handle_notified = " << handle_notified;

//    qDebug() << "Start Re-notify";

//    sev.sigev_notify = SIGEV_THREAD;
//    sev.sigev_notify_function = func_notify;
//    sev.sigev_notify_attributes = NULL;
//    sev.sigev_value.sival_ptr = (mqd_t *)(sv.sival_ptr);

//    mq_notify(handle_notified, &sev);

//    qDebug() << "Re-notify ended\nTry to receive message\n";

//    bytes_read = mq_receive(handle_notified, message_buffer, message_max_size, NULL);

//    if(bytes_read >= 0)
//    {
//        qDebug() << "bytes_read = " << bytes_read << "\nmessage_buffer = " << message_buffer;
//        return;
//    }

//    qDebug() << "empty (none message)\n";
//    return;

//}



static void func_notify(union sigval sv)
{

    struct sigevent sev;
    struct st_thread_misc thr_misc;
    mqd_t handle_notified;
    posix_mq * posix_mq_ptr;
    char message_buffer[8192] = { 0 };
    uint32_t message_max_size;
    ssize_t bytes_read;

    message_max_size = 1024;

    qDebug() << "In func_notify()";

    thr_misc = *((struct st_thread_misc *)(sv.sival_ptr));
    handle_notified = thr_misc.notified;
    posix_mq_ptr = (posix_mq *)(thr_misc.ptr);
    posix_mq_ptr->debug_method();


    qDebug() << "handle_notified = " << handle_notified;

    qDebug() << "Start Re-notify";

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = func_notify;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = (struct st_thread_misc *)(sv.sival_ptr);

    mq_notify(handle_notified, &sev);

    qDebug() << "Re-notify ended\nTry to receive message\n";

    bytes_read = mq_receive(handle_notified, message_buffer, message_max_size, NULL);

    if(bytes_read >= 0)
    {
        qDebug() << "bytes_read = " << bytes_read << "\nmessage_buffer = " << message_buffer;
        posix_mq_ptr->run_notify_thread_func_signal(QString(message_buffer));
        return;
    }

    qDebug() << "empty (none message)\n";
    return;

}


void setup(posix_mq * mq_control, void (*thr_func)(sigval_t), struct st_thread_misc * thr_misc)
{
    qDebug() << "In setup function (from main)";

    mq_control = new posix_mq();

    mq_control->auto_init();

    mq_control->print_info();

    mq_control->setup_notification("", thr_func, thr_misc);

    mq_control->write("Message from QT (setup function)");
}

int32_t main(int32_t argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    struct st_thread_misc thr_misc;
    posix_mq * mq_control;
    void (*thr_func)(sigval_t) = func_notify;

    setup(mq_control, thr_func, &thr_misc);


    return a.exec();
}

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

////    mqd_t notified_handle;
//    struct st_thread_misc thr_misc;
//    posix_mq * mq_control = new posix_mq();


//    mq_control->auto_init();
//    mq_control->print_info();
////    mq_control->setup_notification("", func_notify, &notified_handle);

//    mq_control->setup_notification("", func_notify, &thr_misc);
//    mq_control->write("Message from QT");

//    while(1)
//    {




//        usleep((int32_t)(1.250 * 1.0e6));

//    }




//    return a.exec();
//}
