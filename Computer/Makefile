all: demo/bbb_3

demo/bbb_3: bbb_3.c zhelpers.h
	gcc -o demo/bbb_3 -O0 -g3 -L/usr/local/lib -lzmq bbb_3.c

.PHONY: clean
clean:
	rm -rf Computer/demo/data_final
	rm -rf Computer/demo/bbb_3
