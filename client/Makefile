PROJ=client
OBJS=main.o Client.o LogReader.o LogSender.o ClientException.o data.o Net_base.o Singleton.o Log.o Mutex.o Net_handle.o Tcp_client.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -std=c++0x -I.
LDFLAGS=-lpthread
$(PROJ):$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
SafeList.o:SafeList.h
	$(CC) -c SafeList.h
%.o:%.cpp %.h
	$(CC) $(CFLAGS) $^
clean:
	$(RM) $(PROJ) $(OBJS)
