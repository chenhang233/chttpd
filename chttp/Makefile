HSRCS = src/chttpd.h src/client.h
SRCS = src/chttpd.c src/client.c

chttpd: $(HSRCS) $(SRCS)
	gcc -o chttpd -g $(SRCS)

clean:
	rm -f chttpd  *.o *.s 
