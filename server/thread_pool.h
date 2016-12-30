#ifndef __THREADPOOL03_H_
#define __THREADPOOL03_H_

#include <pthread.h>
#include <deque>
#include <functional>
#include "mutex.h"

// 每一个job都是function对象
class Threadpool
{
private:
  Threadpool(const Threadpool &);
  Threadpool& operator=(const Threadpool &);
public:
  typedef std::function<void()> Task;

  Threadpool(int thread_num = 10);
  ~Threadpool();

  void stop();
  int add_task(const Task &);
  int size();
  Task take();
private:
  volatile bool running_;
  int thread_num_;
  pthread_t *threads_;
  std::deque<Task> task_queue_;
  Mutex mutex_;
  Condition cond_;
private:
  int create_threads();
  static void* thread_func(void *arg);
};

#endif