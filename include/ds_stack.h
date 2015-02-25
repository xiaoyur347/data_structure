#ifndef DATA_STRUCTURE_STACK_H
#define DATA_STRUCTURE_STACK_H

#include <stdlib.h> // for NULL define
#include <bits/functexcept.h>

namespace data_structure
{
template<typename TYPE>
class stack
{
public:
	typedef struct item
	{
		item* next;
		TYPE data;
	}item;
	typedef item* pointer;
	typedef const item* const_pointer;
	stack()
	{
		_M_head = new item;
		_M_head->next = NULL;
	}
	~stack()
	{
		pointer pCur = _M_head->next;
		_M_head->next = NULL;
		
		while (pCur != NULL)
		{
			pointer pNext = pCur->next;
			delete pCur;
			pCur = pNext;
		}
		delete _M_head;
		_M_head = NULL;
	}
	size_t size() const
	{
		size_t i = 0;
		for (pointer pCur = _M_head->next; pCur != NULL; pCur = pCur->next)
		{
			++i;
		}
		
		return i;
	}
	bool empty() const
	{
		return _M_head->next == NULL;
	}
	void push(const TYPE& val)
	{
		pointer pCur = new item;
		pCur->data = val;
		pCur->next = _M_head->next;
		_M_head->next = pCur;
	}
	void pop()
	{
		pointer pHead = _M_head->next;
		if (pHead == NULL)
		{
			return;
		}
		
		_M_head->next = pHead->next;
		delete pHead;
	}
	TYPE &top()
	{
		pointer pHead = _M_head->next;
		if (pHead == NULL)
		{
			std::__throw_out_of_range(__N("stack::_M_range_check"));
		}
		
		return pHead->data;
	}
	const TYPE &top() const
	{
		const_pointer pHead = _M_head->next;
		if (pHead == NULL)
		{
			std::__throw_out_of_range(__N("stack::_M_range_check"));
		}
		
		return pHead->data;
	}
private:
	pointer _M_head;
};

} // namespace data_structure

#endif
