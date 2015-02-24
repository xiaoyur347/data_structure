#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include <stdlib.h> // for NULL define
#include <bits/functexcept.h>

namespace data_structure
{
template<typename TYPE>
class list
{
public:
	typedef struct item
	{
		item* next;
		item* last;
		TYPE data;
	}item;
	typedef item* pointer;
	typedef const item* const_pointer;
	list()
	{
		_M_head = new item;
		_M_head->next = _M_head;
		_M_head->last = _M_head;
	}
	~list()
	{
		clear();
		delete _M_head;
		_M_head = NULL;
	}
	size_t size() const
	{
		size_t i = 0;
		for (pointer pCur = _M_head->next; pCur != _M_head; pCur = pCur->next)
		{
			++i;
		}
		
		return i;
	}
	bool empty() const
	{
		return _M_head->next == _M_head;
	}
	void clear()
	{
		pointer pCur = _M_head->next;
		_M_head->next = _M_head;
		_M_head->last = _M_head;
		
		while (pCur != _M_head)
		{
			pointer pNext = pCur->next;
			delete pCur;
			pCur = pNext;
		}
	}
	TYPE& at(size_t loc)
	{
		size_t i = 0;
		for (pointer pCur = _M_head->next; pCur != _M_head; pCur = pCur->next)
		{
			if (i == loc)
			{
				return pCur->data;
			}
			++i;
		}
		
		std::__throw_out_of_range(__N("slist::_M_range_check"));
	}
	const TYPE& at(size_t loc) const
	{
		size_t i = 0;
		for (const_pointer pCur = _M_head->next; pCur != _M_head; pCur = pCur->next)
		{
			if (i == loc)
			{
				return pCur->data;
			}
			++i;
		}
		
		std::__throw_out_of_range(__N("slist::_M_range_check"));
	}
	void push_back(const TYPE& val)
	{
		pointer pCur = new item;
		pointer pNext = _M_head;
		
		pCur->data = val;
		pCur->next = pNext;
		pCur->last = pNext->last;
		pNext->last->next = pCur;
		pNext->last = pCur;
	}
	void push_front(const TYPE& val)
	{
		pointer pCur = new item;
		pointer pNext = _M_head->next;
		
		pCur->data = val;
		pCur->next = pNext;
		pCur->last = pNext->last;
		pNext->last->next = pCur;
		pNext->last = pCur;
	}
	void insert(size_t loc, const TYPE& val)
	{
		pointer pNext = _M_head->next;
		size_t i = 0;
		for (; pNext != _M_head; pNext = pNext->next)
		{
			if (i == loc)
			{
				break;
			}
			++i;
		}
		
		if (i < loc)
		{
			std::__throw_out_of_range(__N("slist::_M_range_check"));
		}
		
		pointer pCur = new item;
		
		pCur->data = val;
		pCur->next = pNext;
		pCur->last = pNext->last;
		pNext->last->next = pCur;
		pNext->last = pCur;
	}
	void remove(size_t loc)
	{
		pointer pCur = _M_head->next;
		size_t i = 0;
		for (; pCur != _M_head; pCur = pCur->next)
		{
			if (i == loc)
			{
				pCur->last->next = pCur->next;
				pCur->next->last = pCur->last;
				delete pCur;
				return;
			}
			++i;
		}
		
		std::__throw_out_of_range(__N("slist::_M_range_check"));
	}
private:
	pointer _M_head;
};

} // namespace data_structure

#endif
