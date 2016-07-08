PROJ=client
OBJS=main.o Client.o LogReader.o LogSender.o ClientException.o data.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -std=c++0x -I.
$(PROJ):$(OBJS)
	$(CC) $^ -o $@
%.o:%.cpp
	$(CC) $(CFLAGS) $^
clean:
	$(RM) $(PROJ) $(OBJS)
