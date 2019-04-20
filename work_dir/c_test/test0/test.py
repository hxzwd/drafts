
import os
import sys
import ctypes

import mmap

class st_reply(ctypes.Structure):
	_fields_ = [("status", ctypes.c_int32), ("message", ctypes.c_char_p)]



def run_client():
	os.system("./bin_client 127.0.0.1")

ll = ctypes.CDLL("./librpc_test.so")

func_get_reply = ll.func_get_reply
func_get_reply.argtypes = None
func_get_reply.restype = ctypes.POINTER(st_reply)


mm = mmap.mmap(-1, 512)
mm.write("2u3o2c0nf09lskjflskjf923mvnjsf")
p = ctypes.POINTER(ctypes.c_char)(ctypes.c_uint32.from_buffer(mm))
p = ctypes.cast(p, ctypes.c_void_p).value

func_set_shm_ptr = ll.func_set_shm_ptr
func_set_shm_ptr.argtypes = [(ctypes.c_void_p),]

#run_rpc_test = ll.run_rpc_test
#run_rpc_test.argtypes = [(ctypes.c_void_p),]
