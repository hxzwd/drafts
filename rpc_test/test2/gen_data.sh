
#!/bin/bash

FILE_SIZE=2048
FILE_NAME=random_data.bin

dd if=/dev/urandom of=$FILE_NAME bs=$FILE_SIZE count=1

