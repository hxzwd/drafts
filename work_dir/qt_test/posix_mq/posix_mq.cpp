#include "posix_mq.h"

posix_mq::posix_mq(QObject * parent, int32_t msg_max_num, int32_t msg_max_size) :
    QObject(parent),
    MESSAGE_MAX_NUM(msg_max_num),
    MESSAGE_MAX_SIZE(msg_max_size)
{

    default_attr.mq_flags = 0;
    default_attr.mq_maxmsg = MESSAGE_MAX_NUM;
    default_attr.mq_msgsize = MESSAGE_MAX_SIZE;
    default_attr.mq_curmsgs = 0;

    m_src = "";
    m_trg = "";


//    connect(this, SIGNAL(notify_thread_func_signal(QString)), this, SLOT(on_notify_thread_func_signal(QString)));

}

int32_t posix_mq::new_message_queue(char *name, int32_t oflag, int32_t mode, struct mq_attr * attr)
{
    mqd_t mq_handle;
    mq_handle = mq_open(name, oflag, mode, attr);

    if(mq_handle < 0)
    {
        qDebug() << "Error: mq_open()\treturn -1";
        qDebug() << "name = " << name << "\noflag = " << oflag << "\nmode = " << mode << "\nattr (pointer) = " << attr;
    }

    mq_info.insert(QString(name), mq_handle);


    return (int32_t)(mq_handle);

}

int32_t posix_mq::new_message_queue(char *name)
{

    int32_t result;
    int32_t oflag = O_CREAT | O_RDWR | O_NONBLOCK;
    int32_t mode = 0664;

    struct mq_attr * attr = &default_attr;

    result =  new_message_queue(name, oflag, mode, attr);

    return result;

}

int32_t posix_mq::new_message_queue(QString name, int32_t oflag, int32_t mode, mq_attr *attr)
{
    std::string tmp_str = name.toStdString();
    char name_buffer[1024] = { 0 };
    sprintf(name_buffer, "%s", tmp_str.c_str());

    return new_message_queue((char *)(name_buffer), oflag, mode, attr);

}

int32_t posix_mq::new_message_queue(QString name)
{
    std::string tmp_str = name.toStdString();
    char name_buffer[1024] = { 0 };
    sprintf(name_buffer, "%s", tmp_str.c_str());

    return new_message_queue((char *)(name_buffer));

}

void posix_mq::clear_all()
{

    qDebug() << "Close and Unlink loop:";

    foreach(QString key, mq_info.keys())
    {
        mqd_t value = mq_info.value(key);
        qDebug() << "Close handle " << value;
        mq_close(value);
        qDebug() << "Unlink name " << key;
        std::string tmp_str = key.toStdString();
        mq_unlink(tmp_str.c_str());
    }

}

int32_t posix_mq::send_message(QString name, QString message)
{
        mqd_t mq_handle;
        int32_t write_status;
        char message_buffer[8192] = { 0 };

        sprintf(message_buffer, "%s", (message.toStdString()).c_str());

        mq_handle = mq_info.value(name);


        write_status = mq_send(mq_handle, message_buffer, MESSAGE_MAX_SIZE, NULL);

        if(write_status)
        {
            qDebug() << "mq_send error: ";
            qDebug() << "name = " << name << "\nmq_handle = " << mq_handle << "\nmessage_buffer = " << message_buffer << "\nwrite_status = " << write_status;
            return write_status;
        }

        return write_status;

}

QString posix_mq::receive_message(QString name)
{

    mqd_t mq_handle;
    ssize_t bytes_read;

    char message_buffer[8192] = { 0 };
    mq_handle = mq_info.value(name);

    bytes_read = mq_receive(mq_handle, message_buffer, MESSAGE_MAX_SIZE, NULL);

    if(bytes_read >= 0)
    {
        qDebug() << "bytes_read = " << bytes_read << "\message_buffer = " << message_buffer;
        return QString(message_buffer);
    }

    qDebug() << "empty (none message)\n";
    return QString("");

}

void posix_mq::set_source(QString name)
{
    m_src = name;
}

void posix_mq::set_target(QString name)
{
    m_trg = name;
}

int32_t posix_mq::write(QString message)
{
    if(m_trg != "")
    {
        return send_message(m_trg, message);
    }
    return -1;
}

QString posix_mq::read()
{
    if(m_src != "")
    {
        return receive_message(m_src);
    }
    return QString("");
}

void posix_mq::auto_init()
{



    QString _trg = "/test_mq";
    QString _src = "/test_mq_response";

    qDebug() << "auto init with source: " << _src;
    qDebug() << "auto init with target: " << _trg;

    new_message_queue(_trg);
    new_message_queue(_src);

    m_src = _src;
    m_trg = _trg;

}

void posix_mq::print_info()
{
    qDebug() << "mq_info loop throug keys and values:";
    uint32_t counter;

    counter = 0;

    foreach(QString key, mq_info.keys())
    {
        mqd_t value = mq_info.value(key);
        qDebug() << "[" << counter << "]\thandle: " << value << " | name: " << key;
        counter++;
    }

    qDebug() << "[m_trg(target)]\thandle: " << mq_info.value(m_trg) << " | name: " << m_trg;
    qDebug() << "[m_src(source)]\thandle: " << mq_info.value(m_src) << " | name: " << m_src;

}

//void posix_mq::setup_notification(QString name, void (*thr_func)(sigval_t), mqd_t * notified)
//{
//    struct sigevent sev;
//    mqd_t mq_handle;

//    qDebug() << "Start setup notification";

//    if(name == "")
//    {
//        name = m_trg;
//    }
//    mq_handle = mq_info.value(name);
//    (*notified) = mq_handle;


//    sev.sigev_notify = SIGEV_THREAD;
//    sev.sigev_notify_function = thr_func;
//    sev.sigev_notify_attributes = NULL;
//    sev.sigev_value.sival_ptr = notified;

//    mq_notify(mq_handle, &sev);
//}


void posix_mq::setup_notification(QString name, void (*thr_func)(sigval_t), struct st_thread_misc * thr_misc)
{
    struct sigevent sev;
    mqd_t mq_handle;

    qDebug() << "Start setup notification";

    if(name == "")
    {
        name = m_trg;
    }
    mq_handle = mq_info.value(name);
//    (*notified) = mq_handle;

    thr_misc->notified = mq_handle;
    thr_misc->ptr = (void *)(this);

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = thr_func;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = (void *)(thr_misc);

    mq_notify(mq_handle, &sev);
}

void posix_mq::debug_method()
{
    qDebug() << "Called debug_method";
    qDebug() << "this = " << this;
}

//void posix_mq::run_notify_thread_func_signal(QString message)
//{
//    qDebug() << "In run_notify_thread_func_signal()";
//    qDebug() << "Emit signal now... (message = " << message << ")";
//    QString msg("skdfjsklfj");
//    emit notify_thread_func_signal(msg);

//}

//void posix_mq::on_notify_thread_func_signal(QString message)
//{

//    qDebug() << "SLOT: " << "on_notify_thread_func_signal(QString message)";
//    qDebug() << "message = " << message;

//}

void posix_mq::run_notify_thread_func_signal(QString message)
{
    qDebug() << "In run_notify_thread_func_signal()";
    qDebug() << "message = " << message;


    QString name = m_src;
    QString reply_message = message.toUpper();
    int32_t reply_status;

    reply_status = send_message(name, reply_message);

    qDebug() << "[run_notify_thread_func_signal] reply_status = " << reply_status;

}
