PROJ=server
OBJS=server_exception.o log_dao.o server_socket.o log_thread.o log_queue.o server.o main.o
#main.o Server.o LogQueue.o LogThread.o LogDao.o ServerException.o ServerSocket.o
CC=g++
RM=rm -rf
CFLAGS=-c -Wall -std=c++0x -I.
LDFLAGS = -lpthread -lmysqlcppconn
$(PROJ):$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
%.o:%.cpp %.h
	$(CC) $(CFLAGS) $^
clean:
		$(RM) $(PROJ) $(OBJS)


