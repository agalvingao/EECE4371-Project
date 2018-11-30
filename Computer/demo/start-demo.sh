#!/bin/bash

#kill -9 ` ps -e | grep bbb_ | cut -f1 -d ' '` &> /dev/null

rm -f data_final.txt
mkfifo data_final.txt

./bbb_3 "TCP://192.168.8.1:5556"
