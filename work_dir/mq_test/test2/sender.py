
import posix_ipc


class p_mq:

	def __init__(self):
		self.req_name = "/test_mq"
		self.res_name = "/test_mq_response"
		self.req = posix_ipc.MessageQueue(self.req_name)
		self.res = posix_ipc.MessageQueue(self.res_name)

	def write(self, msg):
		self.req.send(msg)

	def read(self)
		if self.res.current_messages > 0:
			return self.res.recieve()
		else:
			return []

	def count(self):
		return (self.req.current_messages, self.res.current_messages)

	def name(self):
		return (self.req.name, self.res.name)






