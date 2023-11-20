HSRCS = chttpd.h client.h
SRCS = chttpd.c client.c

chttpd: $(HSRCS) $(SRCS)
	gcc -o chttpd -g $(SRCS)

clean:
	rm -f chttpd  *.o *.s out