
import numpy as np

from threading import Thread

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


def func_run_server():
	print "Run ThreadedServer in thread"
	print "port = 18812"
	server = ThreadedServer(service, port = 18812)
	server.start()


thr_1 = Thread(target = func_run_server, args = ())


