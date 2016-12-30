#include "thread_pool.h"

#include <iostream>
#include <assert.h>

using namespace std;

Threadpool::Threadpool(int thread_num) : 
  running_(true),
  thread_num_(thread_num),
  mutex_(),
  cond_(mutex_)
{
  create_threads();
}

Threadpool::~Threadpool()
{
   stop();
}

void Threadpool::stop()
{
  if( !running_ )
    return;
 
  running_ = false;
  cond_.wakeAll();

  for(int i = 0; i < thread_num_; ++i)
  {
    pthread_join(threads_[i],NULL);
  }

  free(threads_);
  threads_ = NULL;
}

int Threadpool::add_task(const Task &task)
{
  mutex_.lock();
  task_queue_.push_back(task);
  int size = task_queue_.size();
  mutex_.unlock();
  cond_.wake();
  return size;
}

int Threadpool::size()
{
  mutex_.lock();
  int size = task_queue_.size();
  mutex_.unlock();
  return size;
}

Threadpool::Task Threadpool::take()
{
  Task task = NULL;
  mutex_.lock();
  while( task_queue_.empty() && running_ )
  {
    cond_.wait();
  }
  if( !running_ )
  {
    mutex_.unlock();
    return task;
  }
  assert(!task_queue_.empty());
  task = task_queue_.front();
  task_queue_.pop_front();
  mutex_.unlock();
  return task;
}

int Threadpool::create_threads()
{
  threads_ = (pthread_t*)malloc(sizeof(pthread_t)*thread_num_);

  for(int i = 0; i < thread_num_; ++i)
  {
    pthread_create(&threads_[i],NULL,thread_func,this);
  }
  return 0;
}

void* Threadpool::thread_func(void *arg)
{
  pthread_t tid = pthread_self();
  Threadpool *pool = static_cast<Threadpool*>(arg);
  while(pool->running_)
  {
    Threadpool::Task task = pool->take();
    if( !task )
    {
      cout << "thread " << tid << " will exit\n" << endl;
      break;
    }
    assert(task);
    task();
  }
  return 0;
}