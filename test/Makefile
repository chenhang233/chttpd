test1: 
	gcc -o test -g 01.thread.c

test2: 
	gcc -o test -g  02.sqlite.c -lsqlite3

test3: 
	gcc -o test -g  03.popen_test.c 


test4: 
	gcc -o test -g -I /usr/include/libnl3 -L /usr/lib 04.libnl_test.c 

clean:
	rm -f test  *.o *.s 