
import rpyc

host_addr = "localhost"
port = 18812

c = rpyc.connect(host_addr, port)

c.root.func_test("TEST MESSAGE! HELLO")

