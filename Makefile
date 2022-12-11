

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<


at: main.o clog.o cli.o serial_.o
	$(CC) $(CFLAGS) -o $@ $^


clean:
	-rm at *.o

