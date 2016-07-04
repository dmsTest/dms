PROJ=server
OBJS=main.o Server.o LogQueue.o LogThread.o LogDao.o ServerException.o ServerSocket.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -I.
$(PROJ):$(OBJS)
		$(CC) $^ -o $@
%.o:%.cpp
		$(CC) $(CFLAGS) $^ -lpthread
clean:
		$(RM) $(PROJ) $(OBJS)


