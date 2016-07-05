PROJ=server
OBJS=main.o Server.o LogQueue.o LogThread.o LogDao.o ServerException.o ServerSocket.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -I.
$(PROJ):$(OBJS)
		$(CC) $^ -o $@
LongDao.o:LogDao.cpp LogDao.h
		$(CC) $(CFLAGS) $^ -lpthread
main.o:main.cpp
	$(CC) $(CFLAGS) $^
Server.o:Server.cpp Server.h
	$(CC) $(CFLAGS) $^
LogQueue.o:LogQueue.cpp LogQueue.h
	$(CC) $(CFLAGS) $^
LogThread.o:LogThread.cpp LogThread.h
	$(CC) $(CFLAGS) $^
ServerException.o:ServerException.cpp ServerException.h
	$(CC) $(CFLAGS) $^
ServerSocket.o:ServerSocket.cpp ServerSocket.h
	$(CC) $(CFLAGS) $^
clean:
		$(RM) $(PROJ) $(OBJS)


