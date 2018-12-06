#!/bin/bash

#kill -9 ` ps -e | grep bbb_ | cut -f1 -d ' '` &> /dev/null

#mkfifo data_final

./bbb_3 `cat ../IP_BB | tr -d '\n'`
