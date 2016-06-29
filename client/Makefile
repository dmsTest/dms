PROJ=client
OBJS=main.o Client.o LogReader.o LogSender.o ClientException.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -I.
$(PROJ):$(OBJS)
	$(CC) $^ -o $@
%.o:%.cpp
	$(CC) $(CFLAGS) $^
clean:
	$(RM) $(PROJ) $(OBJS)
