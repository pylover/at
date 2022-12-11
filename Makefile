

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<


at: main.o clog.o cli.o serial.o
	$(CC) $(CFLAGS) -o $@ $^


clean:
	-rm at *.o

