#!/bin/bash

#kill -9 ` ps -e | grep bbb_ | cut -f1 -d ' '` &> /dev/null

#mkfifo data_final

./bbb_3 "tcp://192.168.8.1:5556"
