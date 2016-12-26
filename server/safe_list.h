#ifndef  __SAFELIST_H_
#define __SAFELIST_H_

#include <list>
#include "mutex.h"

#define WAIT_POP_SEC 2

using namespace std;

// thread safe list
template<typename T>
class SafeList
{
public:
	SafeList() : m_mutex(),m_cond(m_mutex)
	{

	}
	~SafeList()
	{

	}
	void push_back(T element)
	{
		m_mutex.lock();
		m_list.push_back(element);
		m_mutex.unlock();
		m_cond.wake();
	}
	bool empty()
	{
		m_mutex.lock();
		bool is_empty = m_list.empty();
		m_mutex.unlock();
		return is_empty;
	}
	int size()
	{
		m_mutex.lock();
		int size = m_list.size();
		m_mutex.unlock();
		return size;
	}
	T pop_front()
	{
		m_mutex.lock();
		while( m_list.empty() )
		{
			m_cond.wait_for_sec(WAIT_POP_SEC);
		}
		if( m_list.empty() )
		{
			m_mutex.unlock();
			return 0;
		}
		T element = m_list.front();
		m_list.pop_front();
		m_mutex.unlock();
		return element;
	}
private:
	list<T> m_list;
	Mutex m_mutex;
	Condition m_cond;
};

#endif