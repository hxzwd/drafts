
import rpyc

class point:
	
	def __init__(self, x, y):
		self.x = x
		self.y = y

	def print_data(self):
		return "(x, y) = ({0}, {1})\n".format(self.x, self.y)

	def func_test(self):
		print "TEST MSG FROM py_test_module.py [class point; method = func_test]"

	def func_call_rpc(self):
		c = rpyc.connect("localhost", 18812)
		c.root.func_test("message from C through Python!")	
