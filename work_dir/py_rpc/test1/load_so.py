



import ctypes


class load_so:
	
	def __init__(self):
		self.lib_handle = ctypes.CDLL("./libclib1.so")
		
		self.alloc_func = self.lib_handle.alloc_memory_block
		self.free_func = self.lib_handle.free_memory_block
		self.dump_func = self.lib_handle.dump_memory_block
		
		#alloc_func.restype = ctypes.POINTER(ctypes.c_char)
		#free_func.argtypes = [ ctypes.POINTER(ctypes.c_char), ]
		
		#alloc_func.restype = ctypes.c_uint64
		#free_func.argtypes = [ ctypes.c_uint64, ]
		self.p = None
		
		self.alloc_func.restype = ctypes.POINTER(ctypes.c_char)
		self.alloc_func.argtypes = [ ctypes.c_uint32, ]
		self.free_func.argtypes = [ ctypes.POINTER(ctypes.c_char), ]
		self.free_func.restype = None
		self.dump_func.argtypes = None
		self.dump_func.restype = None

	def alloc(self, sz):
		self.p = self.alloc_func(sz)
		return self.p
		
	def free(self):
		if self.p != None:
			self.free_func(self.p)
	
	def dump(self):
		self.dump_func()
		

	
