# example11_dir/Makefile
TARGET = prog
OBJS = main.o prog.o foo.o bar.o

prog : CFLAGS = -g
prog : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

prog.o : prog.c
	$(CC) $(CFLAGS) -c prog.c -o prog.o

foo.o : foo.c
	$(CC) $(CFLAGS) -c foo.c -o foo.o

bar.o : bar.c
	$(CC) $(CFLAGS) -c bar.c -o bar.o

clean:
	rm -f $(TARGET) $(OBJS)