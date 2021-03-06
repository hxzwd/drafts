
import posix_ipc


class p_mq:

	def __init__(self):
		self.req_name = "/test_mq"
		self.res_name = "/test_mq_response"
		self.req = posix_ipc.MessageQueue(self.req_name)
		self.res = posix_ipc.MessageQueue(self.res_name)

	def write(self, msg):
		self.req.send(msg)

	def read(self):
		if self.res.current_messages > 0:
			return self.res.receive()
		else:
			return []

	def count(self):
		return (self.req.current_messages, self.res.current_messages)

	def name(self):
		return (self.req.name, self.res.name)

	def print_debug_info(self):
		print "Request posix message queue:\n"\
		"\tname = {0}\nResponse posix message queue:\n"\
		"\tname = {1}".format(self.req.name, self.res.name)

	def quit(self):
		self.write("quit")
	
	def close(self):
		self.req.close()
		self.res.close();

	def unlink(self):
		self.req.unlink()
		self.res.unlink();

	def clean(self):
		self.close()
		self.unlink()





