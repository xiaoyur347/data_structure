#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H

#include <stdlib.h> // for NULL define
#include <bits/functexcept.h>

namespace data_structure
{
template<typename TYPE>
class queue
{
public:
	typedef struct item
	{
		item* next;
		TYPE data;
	}item;
	typedef item* pointer;
	typedef const item* const_pointer;
	queue()
	{
		_M_head = NULL;
		_M_tail = NULL;
	}
	~queue()
	{
		for (pointer pCur = _M_head;pCur != NULL;)
		{
			pointer pNext = pCur->next;
			delete pCur;
			pCur = pNext;
		}
		_M_head = NULL;
		_M_tail = NULL;
	}
	size_t size() const
	{
		size_t i = 0;
		for (pointer pCur = _M_head; pCur != NULL; pCur = pCur->next)
		{
			++i;
		}
		
		return i;
	}
	bool empty() const
	{
		return _M_head == NULL;
	}
	void push(const TYPE& val)
	{
		pointer pCur = new item;
		pCur->data = val;
		pCur->next = NULL;
		
		if (_M_head == NULL)
		{
			_M_head = pCur;
		}
		if (_M_tail != NULL)
		{
			_M_tail->next = pCur;
		}
		_M_tail = pCur;
	}
	void pop()
	{
		pointer pHead = _M_head;
		if (pHead == NULL)
		{
			return;
		}
		
		_M_head = pHead->next;
		delete pHead;
	}
	TYPE &front()
	{
		pointer pHead = _M_head;
		if (pHead == NULL)
		{
			std::__throw_out_of_range(__N("stack::_M_range_check"));
		}
		
		return pHead->data;
	}
	const TYPE &front() const
	{
		const_pointer pHead = _M_head;
		if (pHead == NULL)
		{
			std::__throw_out_of_range(__N("stack::_M_range_check"));
		}
		
		return pHead->data;
	}
private:
	pointer _M_head;
	pointer _M_tail;
};

} // namespace data_structure

#endif
