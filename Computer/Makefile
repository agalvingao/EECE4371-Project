all: demo/bbb_3 demo/data_final

demo/data_final:
	mkfifo demo/data_final

demo/bbb_3: bbb_3.c zhelpers.h
	gcc -o demo/bbb_3 -O0 -g3 -L/usr/local/lib -lzmq bbb_3.c -lzmq

.PHONY: clean
clean:
	rm -rf demo/data_final
	rm -rf demo/bbb_3
