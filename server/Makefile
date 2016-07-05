PROJ=server
OBJS=ServerException.o LogDao.o ServerSocket.o LogThread.o LogQueue.o Server.o main.o
#main.o Server.o LogQueue.o LogThread.o LogDao.o ServerException.o ServerSocket.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -I.
LIBS = -lpthread -lmysqlcppconn
$(PROJ):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)
main.o:main.cpp
	$(CC) $(CFLAGS) $^
Server.o:Server.cpp Server.h
	$(CC) $(CFLAGS) $^
LogQueue.o:LogQueue.cpp LogQueue.h
	$(CC) $(CFLAGS) -o $@ $< 
LogThread.o:LogThread.cpp LogThread.h
	$(CC) $(CFLAGS) -o $@ $<
LogDao.o:LogDao.cpp LogDao.h
	$(CC) $(CFLAGS) -o $@ $< 
ServerException.o:ServerException.cpp ServerException.h
	$(CC) $(CFLAGS) $^
ServerSocket.o:ServerSocket.cpp ServerSocket.h
	$(CC) $(CFLAGS) $^
clean:
		$(RM) $(PROJ) $(OBJS)


