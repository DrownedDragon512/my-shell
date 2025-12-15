CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = shell.o jobs.o parser.o exec.o script.o ui.o

shell: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o shell

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o shell
