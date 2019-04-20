
#!/bin/bash


function swig()
{
	swig2.0 $@;
}

function build()
{
	gcc -fpic -c c_code.c c_code_wrap.c \
	-I/usr/include/python3.4 \
	-I/usr/lib/python3.4 \
#	-I/usr/lib/python3.4/config-3.4m-x86_64-linux-gnu;
	gcc -shared c_code.o c_code_wrap.o -o c_code_module.so \
	-L/usr/lib/python3.4 \
#	-L/usr/lib/python3.4/config-3.4m-x86_64-linux-gnu \
#	-lpython3.4;


}

#swig -python c_code.i

swig3.0 -python -py3 c_code.i
build

