PROJ=client
OBJS=main.o Client.o LogReader.o LogSender.o ClientException.o data.o Singleton.o Log.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -std=c++0x -I.
LDFLAGS=-lpthread
$(PROJ):$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
%.o:%.cpp %.h
	$(CC) $(CFLAGS) $^
clean:
	$(RM) $(PROJ) $(OBJS)
