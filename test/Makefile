test1: 
	gcc -o test -g 01.thread.c

test2: 
	gcc -o test -g  02.sqlite.c -lsqlite3

test3: 
	gcc -o test -g  03.popen_test.c 

test4: 
	gcc -o test -g -I /usr/include/libnl3 -L /usr/lib 04.libnl_test.c 

# gcc 链接库 前一个依赖后一个
test5:  
	gcc -c  -I /usr/include/libnm  -I /usr/include/glib-2.0 -I /usr/lib/aarch64-linux-gnu/glib-2.0/include  05.wifi.c -o test.o 
	gcc test.o -L /usr/lib/aarch64-linux-gnu/ -lnm -lglib-2.0 -lgobject-2.0 -o test

test6:  
	gcc -c  -I /usr/include/libnm  -I /usr/include/glib-2.0 -I /usr/lib/aarch64-linux-gnu/glib-2.0/include  06.wifi_ap_info.c -o test.o 
	gcc test.o -L /usr/lib/aarch64-linux-gnu/ -lnm -lglib-2.0 -lgobject-2.0 -o test





clean:
	rm -f test  *.o *.s 