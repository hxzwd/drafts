
import posix_ipc

mq_name = "/test_mq"

mq_handle = posix_ipc.MessageQueue(mq_name)

mq_handle.send("hello!")


