PROJ=client
OBJS=main.o client.o log_reader.o log_sender.o client_exception.o data.o net_base.o singleton.o client_log.o mutex.o net_handle.o tcp_client.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -std=c++0x -I.
LDFLAGS=-lpthread
$(PROJ):$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
safe_list.o:safe_list.h
	$(CC) -c safe_list.h
%.o:%.cpp %.h
	$(CC) $(CFLAGS) $^
clean:
	$(RM) $(PROJ) $(OBJS)
