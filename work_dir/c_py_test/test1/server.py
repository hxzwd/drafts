
import numpy as np


import rpyc
from rpyc.utils.server import ThreadedServer

class service(rpyc.Service):

	def exposed_echo(self, msg):
		print "Message is {0}\n".format(msg)
	def exposed_func_test(self, msg):
		print "func_test"
		print "msg = {0}\n".format(msg)
		print "msg as byte array (list form) = {0}\n".format(np.frombuffer(msg, dtype = np.uint8).tolist())

if __name__ == "__main__":

	server = ThreadedServer(service, port = 18812)
	server.start()

