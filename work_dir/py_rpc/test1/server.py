
import numpy as np

from load_so import load_so

import rpyc
from rpyc.utils.server import ThreadedServer

class service(rpyc.Service):

	def exposed_echo(self, msg):
		print "Message is {0}\n".format(msg)
	def exposed_func_test(self, msg):
		print "func_test"
		print "msg = {0}\n".format(msg)
		print "msg as byte array (list form) = {0}\n".format(np.frombuffer(msg, dtype = np.uint8).tolist())
	def exposed_func_test_2(self, msg):
		print "return msg[0] = {0}\n".format(msg[0])
		return msg[0]
	def exposed_func_init(self, msg):
		self.o = load_so()
		self.p = self.o.alloc(int(msg))
	def exposed_func_close(self, msg):
		self.o.free()
		self.p = None
	def exposed_func_test_3(self, msg):
		pass
	

if __name__ == "__main__":

	server = ThreadedServer(service, port = 18812)
	server.start()

