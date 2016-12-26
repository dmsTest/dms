#ifndef  __SINGLETON_H_
#define __SINGLETON_H_

#include <pthread.h>

// can't copy construct or copy
class Noncopyable
{
protected:
	Noncopyable(const Noncopyable &);
	Noncopyable& operator=(const Noncopyable &);
public:
	Noncopyable() {}
	~Noncopyable() {}
};

// thread safe singleton, auto destroy
template<typename T>
class Singleton : public Noncopyable
{
public:
	static T* getInstance()
	{
		pthread_once(&m_once,init);
		return m_instance;
	}
private:
	class GC
	{
		~GC()
		{
			// when gc destruct, auto delete the instance
			if( m_instance != NULL)
				delete m_instance;
			m_instance = NULL;
		}
	};
private:
	static T *m_instance;
	static pthread_once_t m_once;
	static GC gc;
	static void init()
	{
		m_instance = new T();
	}
};

template<typename T>
T* Singleton<T>::m_instance = NULL;

template<typename T>
pthread_once_t Singleton<T>::m_once = PTHREAD_ONCE_INIT;

#endif